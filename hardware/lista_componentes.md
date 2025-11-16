Materiais

2.1.1	Plataforma de Prototipagem

Foi utilizada a placa ESP32 como unidade de processamento principal. O ESP32 é um microcontrolador que integra CPU, memória, GPIOs, além de suporte nativo a Wi-Fi e Bluetooth, facilitando a comunicação IoT. Sua escolha justifica-se pela capacidade de processamento superior em relação ao Arduino UNO e pelo suporte direto ao protocolo MQTT. Link de referência para o Datasheet da Série ESP32: https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf
 <img width="499" height="409" alt="image" src="https://github.com/user-attachments/assets/e831b9e2-5607-4f59-abe6-ead2f562ccae" />


2.1.2	Sensor

O sensor utilizado foi o módulo RFID RC522, que opera na frequência de 13,56 MHz e é capaz de realizar leituras de cartões e tags RFID. Sua função é autenticar os usuários cadastrados, permitindo ou negando o acesso ao cofre. Link de referência para Data Specs do Módulo RC522:  http://www.handsontec.com/dataspecs/ RC522.pdf

 <img width="435" height="431" alt="image" src="https://github.com/user-attachments/assets/76998619-e4e7-46ec-be68-d2c5f6e7f85d" />


2.1.3	Atuador

Como atuador, foi empregado o microservo TowerPro SG90, responsável por simular a abertura e o fechamento da trava do cofre. O servo motor é acionado mediante a leitura de uma tag RFID autorizada. Link de referência para o Data Sheet do Micro Servo SG90: http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/ stores/sg90_datasheet.pdf

<img width="474" height="343" alt="image" src="https://github.com/user-attachments/assets/81705626-1d20-49d9-bfb0-a5bceb8fc5ce" />
 

2.1.4	Componentes de Apoio

- LEDs (verde e vermelho) para indicar acesso permitido ou negado;
<img width="179" height="258" alt="image" src="https://github.com/user-attachments/assets/fc157ab4-0007-4096-aaf6-fbc6978d8401" />

 
Fonte: https://www.alamyimages.fr/photo-image-led-rouge-vert-close-up-shot-30949525.html


- Buzzer para sinal sonoro em caso de acesso não autorizado;
<img width="309" height="235" alt="image" src="https://github.com/user-attachments/assets/8b12921a-7922-49df-a87d-d0ce4f888814" />

 
Fonte: Sinalizadores LEDs | Schmersal Brasil


- Jumpers, resistores e protoboard para interligações;
<img width="349" height="422" alt="image" src="https://github.com/user-attachments/assets/d909a406-5b5c-4c10-850b-1248b48a368d" />

 
Fonte: https://www.smartcomponentes.com/




- Fonte de energia 5V (via USB ou adaptador).
<img width="389" height="367" alt="image" src="https://github.com/user-attachments/assets/f5c0c54e-81ae-4f60-a4fb-e35a335d51e0" />

 
Fonte: https://www.tecnotronics.com.br/

