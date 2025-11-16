# Lista detalhada de componentes

## Tabela resumida

| Item | Quantidade | Observações |
|------|------------|-------------|
| ESP32 DevKit V1 | 1 | MCU principal com Wi-Fi/MQTT |
| Módulo RFID RC522 | 1 | Comunicação SPI (3.3 V) |
| Servo motor SG90 | 1 | Travamento mecânico do cofre |
| Fonte 5 V / 2 A | 1 | Alimentação do conjunto |
| Protoboard 830 pontos | 1 | Montagem do circuito |
| Jumpers macho-macho | 20 | Ligações gerais |
| Jumpers macho-fêmea | 5 | Alimentação do servo |
| Resistores 220 Ω | 2 | Limitadores para LEDs |
| LED verde | 1 | Status autorizado |
| LED vermelho | 1 | Status negado |
| Buzzer 5 V | 1 | Alarme opcional |
| Botão tipo push | 1 | Reset manual |
| Cartões RFID (MF1S50) | 2 | Tag autorizada e visitante |
| Cabo micro-USB | 1 | Upload do firmware |

> Fotos e diagramas: consulte `hardware/fritzing_diagrama.png` e `hardware/prototipo_montado.png`.

## Descrição dos principais módulos

### 2.1.1 Plataforma de Prototipagem

Foi utilizada a placa **ESP32 DevKit V1** como unidade de processamento principal. O ESP32 integra CPU, memória, GPIOs e suporta Wi-Fi/Bluetooth de forma nativa, o que simplifica a comunicação IoT e o uso de MQTT diretamente no microcontrolador. A escolha foi motivada pela capacidade de processamento superior em relação ao Arduino UNO.  
Datasheet: [ESP32 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)  
![ESP32](https://github.com/user-attachments/assets/e831b9e2-5607-4f59-abe6-ead2f562ccae)

### 2.1.2 Sensor RFID

O sensor utilizado é o **módulo RFID RC522**, operando em 13,56 MHz. Ele autentica os usuários cadastrados e informa ao ESP32 se o acesso deve ser liberado ou negado.  
Data Specs: [RC522](http://www.handsontec.com/dataspecs/RC522.pdf)  
![RC522](https://github.com/user-attachments/assets/76998619-e4e7-46ec-be68-d2c5f6e7f85d)

### 2.1.3 Atuador

O atuador é o **microservo TowerPro SG90**, responsável por acionar a trava do cofre. Assim que uma tag é reconhecida como autorizada, o servo abre o mecanismo, retornando ao estado fechado após o tempo configurado.  
Datasheet: [Servo SG90](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)  
![Servo SG90](https://github.com/user-attachments/assets/81705626-1d20-49d9-bfb0-a5bceb8fc5ce)

### 2.1.4 Componentes de apoio

- LEDs (verde/vermelho) para indicar acesso permitido ou negado.  
  ![LEDs](https://github.com/user-attachments/assets/fc157ab4-0007-4096-aaf6-fbc6978d8401)  
  Fonte: alamyimages.fr
- Buzzer para alerta sonoro em caso de tentativa não autorizada.  
  ![Buzzer](https://github.com/user-attachments/assets/8b12921a-7922-49df-a87d-d0ce4f888814)  
  Fonte: Schmersal Brasil
- Jumpers, resistores e protoboard para as interligações.  
  ![Jumpers](https://github.com/user-attachments/assets/d909a406-5b5c-4c10-850b-1248b48a368d)  
  Fonte: smartcomponentes.com
- Fonte de energia 5 V (USB ou adaptador).  
  ![Fonte 5V](https://github.com/user-attachments/assets/f5c0c54e-81ae-4f60-a4fb-e35a335d51e0)  
  Fonte: Tecnotronics
