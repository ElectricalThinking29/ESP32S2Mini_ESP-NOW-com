# Programming the ESP32‑S2 Mini board with Wi‑Fi using the ESP‑NOW protocol

Other language: [Tiếng Việt](https://github.com/ElectricalThinking29/ESP32S2Mini_ESP-NOW-com/blob/main/vietnamese/README.md)

## Overview
- The article will cover:
  - Features available on the ESP32‑S2 Mini board
  - Things to keep in mind when using the Wi‑Fi functionality of the ESP32‑S2
  - Setting up an environment for programming the ESP32‑S2 Mini board
  - Code, uploading the code, and results achieved

## About the ESP32‑S2 Mini board
### ESP32‑S2 Mini board
<div align="center">

| Front view | Rear view |
|:---:|:---:|
|<img src="https://github.com/ElectricalThinking29/ESP32S2Mini_ESP-NOW-com/blob/main/images/esp32s2mini_front_brightened.jpg" width="400" height="400" />|<img src="https://github.com/ElectricalThinking29/ESP32S2Mini_ESP-NOW-com/blob/main/images/esp32s2mini_rear_brightened.jpg" width="400" height="400" />|

| Technical specifications | Details |
|:---|:---|
|CPU operating frequency | 240 MHz (*) |
|APB block supply frequency | 80 MHz (**) |
|Operating voltage | 1.8 – 3.6 VDC |
|Current rating | 68 – 310 mA |
|Connection + power port | USB‑C |

</div>
(*) : Can be set to 80, 160 or 240 MHz. The default (when programming with the Arduino IDE or PlatformIO) is 240 MHz.
<br />(**): The default (when programming with the Arduino IDE or PlatformIO) is 80 MHz.


### Features available on the WEMOS ESP32‑S2 Mini board
| Feature | Pin name(s) | Notes |
|:---|:---|:---|
| GPIO | 1–14, 15–18, 33–40 | up to 27 GPIOs |
| RTC GPIO | 1–14 | |
| ADC | ADC1; ADC2 | Each bank has 10 channels |
| DAC | DAC1; DAC2 | Each bank has 1 channel |
| UART | UART1 | UART0 is not exposed because it’s used for the USB port.<br />If you use `SoftwareSerial.h`, you can assign any two unused GPIOs as Tx and Rx (+) |
| SPI | MISO(SDO), MOSI(SDI), SCK(SCLK), SS | If you use the `SPI.h` library, you can assign any four unused GPIOs to the four SPI pins (+) |
| I²C | SCL, SDA | If you use the `Wire.h` library, you can assign any two unused GPIOs to the two I²C pins (+) |
| Touch sensor pins | TOUCH1–14 | |
| PWM | Any GPIO | Default frequency: 1 kHz. With `ledcSetup()` you can raise the PWM frequency up to 40 MHz |
| USB | Type‑C | |
| RF | Wi‑Fi | No Bluetooth |

(+) : Some pins cannot perform one or all of these functions.<br />
- Pins that require special attention include:
  - GPIO 0: Boot pin
  - GPIO 34–39: Input only
- It’s best to use each “hard” pin for its intended function so the microcontroller runs stably and at peak performance.
<br />

### Pinout map
![ESP32‑S2 Mini Pinout](/images/ESP32S2MiniPinoutVer2.jpg)

## Note when enabling Wi‑Fi
Once you enable Wi‑Fi on the ESP32‑S2, ADC2 can no longer be used.<br /><br />
_"Because ADC2 is also used by Wi‑Fi, attempts to read with `adc2_get_raw()` may fail while the program is running between `esp_wifi_start()` and `esp_wifi_stop()`"_ <br /><br />
(Quoted from [Reference 3](# References))

## Setting up the programming environment
### Using PlatformIO in VS Code
1. Create a project  
    - Select board name: **WEMOS LOLIN S2**.
2. Check the configuration and edit `platformio.ini` if needed  
    - You can refer to this [example `platformio.ini`](/Code/platformio.ini).
3. Write your program in `src/main.cpp`  
    - Project layout:
```
[Project]
 |__[.pio]
 |__[.vscode]
 |__[include]
 |__[lib]
 |__[src]
     |__main.cpp <------ Viết code ở đây
 |__[test]
 |__.gitignore
 |__platformio.ini
```

### Using the Arduino IDE


## Code, Uploading and Results
### [Optional] Retrieve the MAC address of the ESP32 board
#### MAC Address
- The MAC address is a unique identifier for the device, assigned by the manufacturer.
- It consists of 48 bits (6 bytes), e.g.: `12:34:56:78:9A:BC`.
- You do **not** need the recipient’s MAC address to send an ESP‑NOW packet.  
  You can use the broadcast address `FF:FF:FF:FF:FF:FF` to transmit packets over ESP‑NOW; any device listening for ESP‑NOW will receive them.

#### Program (code)
- The code that obtains the MAC address of your ESP32 board is available [here](/Code/src/getMAC_v0-4.cpp).  
  Just copy and paste it into `main.cpp`.

#### Overview
- The program prints the ESP32’s MAC address to the Serial console (baudrate = 115200).

### Programming an ESP32 to send ESP‑NOW packets
#### Program (code)
- The code for sending ESP‑NOW packets from an ESP32 is available [here](/Code/src/Sender_v1-2_mini.cpp).  
  Copy and paste it into `main.cpp`.

#### Overview
- Initializes the Wi‑Fi module and enables Wi‑Fi.
- Creates a struct containing the MAC address of the target device.
- Registers that target with the esp‑now module.
- Sends one packet every second without using `delay()`.
- Toggles an LED on success; turns it off if sending fails.

### Programming an ESP32 to receive ESP‑NOW packets
#### Program (code)
- The code for receiving ESP‑NOW packets is available [here](/Code/src/Receiver_v0-4_mini.cpp).  
  Copy and paste it into `main.cpp`.

#### Overview
- Initializes the Wi‑Fi module and enables Wi‑Fi.
- Registers an interrupt handler to process incoming ESP‑NOW packets.
- Prints received packets to the Serial console (baudrate = 115200).

### YouTube
[Wi‑Fi on the ESP32‑S2 Mini board](https://youtu.be/QS1hqV-2Io4)

## References
1. [S2 mini - WEMOS ](https://www.wemos.cc/en/latest/s2/s2_mini.html)
2. [ESP32S2Mini_OnOffLED-Example - (Me)Electricalthinking29](https://github.com/ElectricalThinking29/ESP32S2Mini_OnOffLED-Example/tree/main)
3. [Analog to Digital Converter (ADC) - Espressif Systems (Shanghai) Co., Ltd](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32s2/api-reference/peripherals/adc.html)
4. [ESP32 S2 Mini](https://www.sudo.is/docs/esphome/boards/esp32s2mini/)
5. [ESP32-S2 Series datasheet - Espressif Systems (Shanghai) Co., Ltd](https://www.espressif.com/sites/default/files/documentation/esp32-s2_datasheet_en.pdf)
6. [ESP32 SPI Communication: Set Pins, Multiple SPI Bus Interfaces, and Peripherals (Arduino IDE) - Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-spi-communication-arduino/)
