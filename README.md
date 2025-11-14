# Cofre-Inteligente-IoT
Projeto de IoT sobre Cofre Inteligente
# Cofre Inteligente IoT com ESP32, RFID e MQTT

Sistema de acesso seguro baseado em RFID, ESP32 e comunicação MQTT.  
O cofre se abre somente quando uma tag autorizada é aproximada do sensor RFID.  
O projeto utiliza Node-RED para visualização em dashboard e MQTT Explorer/ HiveMQ para monitoramento das mensagens.

---

## 📌 Funcionalidades

- Leitura de RFID (RC522)
- Autorização e negação de acesso via ESP32
- Acionamento de servo motor (abertura/fechamento)
- Envio de mensagens MQTT para broker (status, tags lidas)
- Recebimento de comandos MQTT (forçar abrir, travar, reset)
- Dashboard no Node-RED
- Log completo via MQTT Explorer

---

## 🛠️ Componentes utilizados

| Componente | Quantidade |
|-----------|------------|
| ESP32 DevKit V1 | 1 |
| Módulo RFID RC522 | 1 |
| Servo Motor SG90 | 1 |
| Jumpers macho/macho | vários |
| Fonte 5V | 1 |
| Protoboard | 1 |

> Lista completa disponível em `/hardware/lista_componentes.md`.

---

## 📡 Fluxo do sistema

1. O usuário aproxima a tag RFID do RC522.  
2. O ESP32 lê o UID e verifica em uma lista de tags autorizadas.  
3. Se autorizado → envia MQTT “cofre/estado = aberto”, aciona servo e abre o cofre.  
4. Se negado → envia MQTT “cofre/estado = acesso_negado”.  
5. Node-RED exibe status em tempo real.  
6. MQTT Explorer registra todas as mensagens trocadas.  

---

## 🌐 Arquitetura IoT (Resumo)

- **ESP32**: leitura RFID + controle do servo + MQTT
- **Broker MQTT (HiveMQ Cloud ou Mosquitto)**: comunicação
- **Node-RED**: dashboard + tratamento de eventos
- **MQTT Explorer**: visualização avançada dos tópicos

> Fluxograma completo disponível em `/hardware/fritzing_diagrama.png`.

---

## 🧪 Resultados (Evidências)

As fotos/prints estão disponíveis na pasta:

```
/hardware
/node-red
/mqtt
```

**Evidências listadas:**
- Protótipo montado  
- Tag autorizada (LED verde no painel)  
- Tag negada (alerta vermelho)  
- Dashboard do Node-RED  
- Log do MQTT Explorer  

---

## 🎥 Vídeo de demonstração

**[INSERIR LINK AQUI]**

---

## 📁 Repositório contendo código e fluxos

- Firmware ESP32: `/software/firmware_esp32.ino`  
- Flow Node-RED: `/node-red/flow.json`  
- Prints do dashboard: `/node-red/dashboard_print.png`  
- Logs MQTT: `/mqtt/mqtt_messages_print.png`

---

## ▶ Como reproduzir

1. Faça upload do firmware no ESP32 (Arduino IDE).  
2. Importe o fluxo Node-RED usando `/node-red/flow.json`.  
3. Configure seu broker MQTT (HiveMQ ou Mosquitto local).  
4. Conecte o RC522 ao ESP32 conforme diagrama `/hardware/fritzing_diagrama.png`.  
5. Abra o dashboard no Node-RED (`http://localhost:1880/ui`).  
6. Teste aproximando as tags ao leitor.

---

## 📝 Autor

**Pyettro Ziroldo**
**Talita Ozaki Bearzotti**
**Everton Celso dos Santos Filho**
Aluno do curso de Tecnologia – IoT e Sistemas Embarcados

---

## 📄 Licença

Este projeto está sob a licença MIT.  
Ver arquivo `LICENSE`.


