# Cofre Inteligente IoT com ESP32, RFID e MQTT

Sistema de acesso seguro baseado em RFID, ESP32 e comunicação MQTT.  
O cofre só é liberado para tags autorizadas, registra telemetria em tópicos MQTT e oferece dashboard no Node-RED para monitorar e enviar comandos remotos.

---

## 📁 Estrutura do repositório

```
hardware/      → Lista de componentes + diagramas e fotos
software/      → Firmware do ESP32 e documentação
node-red/      → Fluxo pronto para importação + print do dashboard
mqtt/          → Capturas das mensagens publicadas
resultados/    → Instruções de teste e medições de tempo
```

---

## 📌 Funcionalidades implementadas

- Leitura de tags RFID (RC522) com validação local.
- Controle do servo SG90 que aciona a trava do cofre.
- Publicação MQTT (`cofre/status`, `cofre/tag`, `cofre/diagnostico`) e assinatura de `cofre/comando`.
- Comandos remotos: abrir, travar, ping (diagnóstico) e reset.
- Dashboard Node-RED com indicadores, histórico de tags e botões de ação.
- Registro de tempos críticos no arquivo `resultados/medicoes.csv`.

---

## 🛠️ Componentes principais

| Componente | Quantidade |
|-----------|------------|
| ESP32 DevKit V1 | 1 |
| Módulo RFID RC522 | 1 |
| Servo Motor SG90 | 1 |
| Fonte 5 V / 2 A | 1 |
| Protoboard + jumpers | 1 |
| LEDs verde/vermelho + resistores | 2 |
| Buzzer 5 V | 1 |

Lista detalhada e observações em `/hardware/lista_componentes.md`.  
Diagrama de ligação em `/hardware/fritzing_diagrama.png`.

---

## 📡 Fluxo do sistema

1. O ESP32 conecta ao Wi-Fi e ao broker MQTT configurado.  
2. O RC522 lê o UID das tags próximas.  
3. Tags autorizadas (lista em `firmware_esp32.ino`) disparam a abertura do servo.  
4. Tags não autorizadas mantêm o servo fechado e acionam alerta sonoro/visual.  
5. Todos os eventos são publicados nos tópicos MQTT para monitoramento.  
6. Node-RED consome os tópicos, exibe no dashboard e pode enviar comandos.

Esquema visual disponível em `/hardware/fritzing_diagrama.png`.

---

## 🧪 Evidências e medições

- Fotos/diagramas: `hardware/prototipo_montado.png` e `hardware/fritzing_diagrama.png`.  
- Prints do dashboard: `node-red/dashboard_print.png`.  
- Captura do log MQTT: `mqtt/mqtt_messages_print.png` + `mqtt/mqtt_messages_print.txt`.  
- Fluxo Node-RED pronto: `node-red/flow.json`.  
- Tempos medidos: `resultados/medicoes.csv`.  
- Passo a passo do ensaio: `resultados/instrucoes.txt`.
- Descrição textual com evidências adicionais: `hardware/Funcionamento.md`.

---

## 🖥️ Simulação no Wokwi

- Projeto final: [https://wokwi.com/projects/447978924553592833](https://wokwi.com/projects/447978924553592833)
- Arquivos prontos para importação: pasta `/wokwi` (contém `diagram.json`, `sketch.ino` e instruções).
- Para importar manualmente:
  1. Crie um novo projeto ESP32 no Wokwi.
  2. Cole o conteúdo de `wokwi/diagram.json` em **File → Save a copy → Import Diagram**.
  3. Substitua o código pelo `wokwi/sketch.ino`.
  4. Ajuste credenciais MQTT/Wi-Fi, inicie a simulação e utilize o RC522/servo/LEDs virtuais.

---

## 🎥 Vídeo de demonstração

[Link video](https://youtu.be/b8zRZoJECz4)

---

## ▶ Como reproduzir (passo a passo)

1. **Firmware**
   - Abra `software/firmware_esp32.ino` na Arduino IDE.
   - Atualize `WIFI_SSID`, `WIFI_PASSWORD` e, se necessário, `MQTT_HOST`.
   - Instale as bibliotecas WiFi, PubSubClient, MFRC522, Servo e ArduinoJson.
   - Faça o upload para o ESP32 e monitore o serial (115200).
2. **Hardware**
   - Siga o diagrama em `hardware/fritzing_diagrama.png`.
   - Conecte o servo ao pino 14 e o RC522 aos pinos SPI (5/18/19/23/27).
3. **Broker MQTT**
   - Utilize HiveMQ, Mosquitto local ou outro broker compatível.
   - Verifique os tópicos `cofre/status`, `cofre/tag`, `cofre/diagnostico` e `cofre/comando`.
4. **Node-RED**
   - Importar `node-red/flow.json`.
   - Ajustar o nó "Broker Cofre" com o host/porta do seu servidor MQTT.
   - Abrir `http://localhost:1880/ui` para visualizar o dashboard.
5. **Testes**
   - Aproximar tags autorizadas e não autorizadas.
   - Validar se o servo abre/fecha, se os LEDs acendem corretamente e se o Node-RED recebe/publica comandos.

---

## 📊 Resultados resumidos

- Conexão Wi-Fi + MQTT: ~3 s após reinício.
- Leitura RFID autorizada: 185 ms.
- Abertura do servo: ~620 ms (0° → 90°).  
Mais valores estão em `resultados/medicoes.csv`.

---

## ▶ Guia rápido (resumo do relatório)

1. Faça upload do firmware no ESP32 (Arduino IDE).  
2. Importe o fluxo Node-RED usando `/node-red/flow.json`.  
3. Configure seu broker MQTT (HiveMQ ou Mosquitto local).  
4. Conecte o RC522 ao ESP32 conforme diagrama `/hardware/fritzing_diagrama.png`.  
5. Abra o dashboard no Node-RED (`http://localhost:1880/ui`).  
6. Teste aproximando as tags ao leitor.

---

## 📝 Autores

**Pyettro Ziroldo**  
**Talita Ozaki Bearzotti**  
**Everton Celso dos Santos Filho**  

Alunos do curso de Tecnologia – IoT e Sistemas Embarcados.

---

## 📄 Licença

Projeto disponível sob licença MIT – consulte `LICENSE`.
