#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <ArduinoJson.h>

// ===== CONFIGURAÇÕES DE REDE (edite para o seu ambiente) =====
const char *WIFI_SSID = "SUA_REDE_WIFI";
const char *WIFI_PASSWORD = "SUA_SENHA_WIFI";

const char *MQTT_HOST = "broker.hivemq.com";
const uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_ID = "cofre-esp32";
const char *TOPICO_STATUS = "cofre/status";
const char *TOPICO_TAG = "cofre/tag";
const char *TOPICO_DIAGNOSTICO = "cofre/diagnostico";
const char *TOPICO_COMANDO = "cofre/comando";

// ===== PINAGEM =====
static const uint8_t PINO_SS = 5;
static const uint8_t PINO_RST = 27;
static const uint8_t PINO_SERVO = 14;
static const uint8_t PINO_LED_VERDE = 26;
static const uint8_t PINO_LED_VERMELHO = 25;
static const uint8_t PINO_BUZZER = 33;
static const uint8_t CANAL_BUZZER = 0;

static const uint8_t ANGULO_FECHADO = 0;
static const uint8_t ANGULO_ABERTO = 90;

struct TagAutorizada {
  const char *uid;
  const char *nome;
};

TagAutorizada tags[] = {
    {"73:2A:1B:5C", "Administrador"},
    {"A1:B2:C3:D4", "Usuário 01"},
    {"AA:BB:CC:11", "Usuário 02"}};

MFRC522 leitor(PINO_SS, PINO_RST);
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
Servo servo;

bool cofreAberto = false;
unsigned long ultimoEnvioDiag = 0;

String uidParaString(MFRC522::Uid *uid) {
  String s;
  for (byte i = 0; i < uid->size; i++) {
    if (uid->uidByte[i] < 0x10) {
      s += "0";
    }
    s += String(uid->uidByte[i], HEX);
    if (i < uid->size - 1) {
      s += ":";
    }
  }
  s.toUpperCase();
  return s;
}

bool buscarTag(const String &uid, const char **nome) {
  for (auto &tag : tags) {
    if (uid.equalsIgnoreCase(tag.uid)) {
      if (nome) {
        *nome = tag.nome;
      }
      return true;
    }
  }
  return false;
}

void publicar(const char *topico, const JsonDocument &doc, bool retain = false) {
  char buffer[256];
  size_t n = serializeJson(doc, buffer);
  mqtt.publish(topico, buffer, n, retain);
}

void publicarStatus(const String &estado, uint32_t tempoMs = 0) {
  StaticJsonDocument<200> doc;
  doc["estado"] = estado;
  doc["tempo_ms"] = tempoMs;
  doc["wifi"] = WiFi.isConnected() ? "ok" : "falha";
  doc["mqtt"] = mqtt.connected() ? "ok" : "falha";
  publicar(TOPICO_STATUS, doc);
}

void publicarDiagnostico() {
  StaticJsonDocument<200> doc;
  doc["uptime"] = millis() / 1000;
  doc["servo"] = cofreAberto ? "aberto" : "fechado";
  doc["rssi"] = WiFi.RSSI();
  publicar(TOPICO_DIAGNOSTICO, doc);
}

uint32_t moverServo(bool abrir) {
  uint32_t inicio = millis();
  uint8_t posInicial = cofreAberto ? ANGULO_ABERTO : ANGULO_FECHADO;
  uint8_t posFinal = abrir ? ANGULO_ABERTO : ANGULO_FECHADO;
  if (posInicial == posFinal) {
    return 0;
  }

  if (posInicial < posFinal) {
    for (uint8_t pos = posInicial; pos <= posFinal; pos++) {
      servo.write(pos);
      delay(5);
    }
  } else {
    for (int pos = posInicial; pos >= posFinal; pos--) {
      servo.write(pos);
      delay(5);
    }
  }

  cofreAberto = abrir;
  digitalWrite(PINO_LED_VERDE, abrir ? HIGH : LOW);
  digitalWrite(PINO_LED_VERMELHO, abrir ? LOW : HIGH);
  return millis() - inicio;
}

void sinalNegado() {
  ledcWriteTone(CANAL_BUZZER, 1500);
  delay(150);
  ledcWriteTone(CANAL_BUZZER, 0);
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERMELHO, HIGH);
}

void conectarWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando-se ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nWi-Fi conectado, IP: %s\n", WiFi.localIP().toString().c_str());
}

void conectarMQTT() {
  while (!mqtt.connected()) {
    Serial.println("Conectando ao broker MQTT...");
    if (mqtt.connect(MQTT_CLIENT_ID)) {
      Serial.println("MQTT conectado!");
      mqtt.subscribe(TOPICO_COMANDO);
      publicarStatus("aguardando_tag");
    } else {
      Serial.print("Falha MQTT, rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

void tratarComando(const JsonDocument &doc) {
  const char *acao = doc["acao"] | "";
  if (!acao || strlen(acao) == 0) {
    return;
  }

  if (strcmp(acao, "abrir") == 0) {
    uint32_t tempo = moverServo(true);
    publicarStatus("aberto_remote", tempo);
  } else if (strcmp(acao, "travar") == 0) {
    uint32_t tempo = moverServo(false);
    publicarStatus("fechado_remote", tempo);
  } else if (strcmp(acao, "ping") == 0) {
    publicarDiagnostico();
  } else if (strcmp(acao, "reset") == 0) {
    ESP.restart();
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload, length);
  if (error) {
    Serial.println("JSON inválido no comando MQTT");
    return;
  }
  tratarComando(doc);
}

void setup() {
  Serial.begin(115200);

  pinMode(PINO_LED_VERDE, OUTPUT);
  pinMode(PINO_LED_VERMELHO, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  ledcSetup(CANAL_BUZZER, 2000, 10);
  ledcAttachPin(PINO_BUZZER, CANAL_BUZZER);

  SPI.begin(18, 19, 23, PINO_SS);
  leitor.PCD_Init();
  servo.attach(PINO_SERVO);
  servo.write(ANGULO_FECHADO);
  cofreAberto = false;
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERMELHO, HIGH);

  conectarWiFi();
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(mqttCallback);
  conectarMQTT();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWiFi();
  }

  if (!mqtt.connected()) {
    conectarMQTT();
  }

  mqtt.loop();

  if (leitor.PICC_IsNewCardPresent() && leitor.PICC_ReadCardSerial()) {
    String uid = uidParaString(&leitor.uid);
    const char *nome = "desconhecido";
    bool autorizada = buscarTag(uid, &nome);

    StaticJsonDocument<200> doc;
    doc["uid"] = uid;
    doc["autorizado"] = autorizada;
    doc["nome"] = nome;
    publicar(TOPICO_TAG, doc);

    if (autorizada) {
      uint32_t tempo = moverServo(true);
      publicarStatus("aberto", tempo);
      delay(3000);
      tempo = moverServo(false);
      publicarStatus("fechado", tempo);
    } else {
      sinalNegado();
      publicarStatus("acesso_negado");
    }

    leitor.PICC_HaltA();
    leitor.PCD_StopCrypto1();
  }

  if (millis() - ultimoEnvioDiag > 30000) {
    publicarDiagnostico();
    ultimoEnvioDiag = millis();
  }
}
