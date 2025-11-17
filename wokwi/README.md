# Simulação no Wokwi

Esta pasta contém todos os arquivos necessários para reproduzir o Cofre Inteligente no [Wokwi](https://wokwi.com).

## Estrutura

- `diagram.json` – conexões dos componentes (ESP32 + RC522 + servo + LEDs + buzzer) alinhadas ao firmware oficial.
- `sketch.ino` – cópia do firmware usado no repositório, pronta para colar no editor do Wokwi.

## Como usar

1. Acesse [https://wokwi.com/projects/new/esp32](https://wokwi.com/projects/new/esp32).
2. Abra o menu `File → Save a copy… → Import JSON` e cole o conteúdo de `diagram.json`.
3. Substitua o conteúdo do `sketch.ino` do Wokwi pelo arquivo desta pasta.
4. Ajuste `WIFI_SSID`/`WIFI_PASSWORD`/`MQTT_HOST` no código, se necessário.
5. Clique em **Start Simulation** e utilize o leitor RFID virtual, servo, LEDs e buzzer conforme descrito no README principal.

> Você também pode clicar em **File → Upload Project Zip** e enviar um `.zip` contendo exatamente os arquivos desta pasta para importar tudo de uma vez.
