# Firmware ESP32 documentado

## Visão geral
O firmware `firmware_esp32.ino` implementa o controle completo do Cofre Inteligente utilizando um ESP32, leitor RFID RC522, servo motor SG90 e comunicação MQTT.

### Bibliotecas utilizadas
- `WiFi.h` – conexão à rede Wi-Fi.
- `PubSubClient.h` – cliente MQTT.
- `SPI.h` e `MFRC522.h` – interface com o sensor RFID.
- `Servo.h` – controle do servo.
- `ArduinoJson.h` – serialização e parsing de mensagens JSON.

### Tópicos MQTT
- `cofre/status` – estado atual (aberto, fechado, acesso_negado, etc.).
- `cofre/tag` – UID e resultado de cada leitura RFID.
- `cofre/diagnostico` – uptime, força do sinal Wi-Fi e posição do servo.
- `cofre/comando` – comandos recebidos (abrir, travar, ping, reset).

### Fluxo principal
1. Conecta ao Wi-Fi e ao broker MQTT configurados.
2. Inicializa o RC522 e o servo, mantendo o cofre travado.
3. Lê tags RFID continuamente:
   - Caso a tag esteja na lista autorizada (`tags[]`), abre o servo, publica os tópicos e fecha após 3 segundos.
   - Caso contrário, aciona alerta sonoro/visual e publica `acesso_negado`.
4. Processa comandos MQTT para abrir/travar remotamente, responder ping ou reiniciar o ESP32.
5. Publica diagnósticos periódicos (a cada 30 s) para acompanhamento remoto.

### Adaptações sugeridas
- Atualize `WIFI_SSID`, `WIFI_PASSWORD` e `MQTT_HOST` antes do upload.
- Cadastre novos usuários adicionando entradas na estrutura `tags[]`.
- Ajuste os ângulos `ANGULO_FECHADO` e `ANGULO_ABERTO` conforme a mecânica do cofre.
- Caso utilize um broker autenticado, configure `mqtt.connect(MQTT_CLIENT_ID, usuario, senha)`.

## Pinagem recomendada
| Componente | ESP32 |
|------------|-------|
| RC522 SDA  | GPIO 5 |
| RC522 SCK  | GPIO 18 |
| RC522 MOSI | GPIO 23 |
| RC522 MISO | GPIO 19 |
| RC522 RST  | GPIO 27 |
| Servo Sinal| GPIO 14 |
| LED verde  | GPIO 26 |
| LED vermelho | GPIO 25 |
| Buzzer     | GPIO 33 |

## Processo de teste
1. Abra a Arduino IDE, selecione a placa *ESP32 DevKit v1* e a porta correta.
2. Instale as bibliotecas necessárias pelo Library Manager.
3. Compile e faça o upload do `firmware_esp32.ino`.
4. Abra o monitor serial (115200) para acompanhar logs.
5. Utilize o MQTT Explorer ou o fluxo Node-RED para observar os tópicos descritos.
