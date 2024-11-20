# Lập trình bảng mạch ESP32-S2 mini giao tiếp qua WiFi dùng giao thức ESP-NOW

## Tổng quan
- Bài viết sẽ trình bày về:
  - Các chức năng có thể dùng được trên bảng mạch ESP32-S2 mini
  - Điều cần lưu ý khi sử dụng chức năng WiFi của ESP32-S2.
  - Thiết lập môi trường để lập trình board ESP32-S2 mini
  - Code, nạp code, kết quả đạt được.
 
## Về bảng mạch ESP32-S2 mini
### Bảng mạch ESP32-S2 mini
<div align="center">

| Mặt trước | Mặt sau |
|:---:|:---:|
|<img src="https://github.com/ElectricalThinking29/ESP32S2Mini_ESP-NOW-com/blob/main/images/esp32s2mini_front_brightened.jpg" width="400" height="400" />|<img src="https://github.com/ElectricalThinking29/ESP32S2Mini_ESP-NOW-com/blob/main/images/esp32s2mini_rear_brightened.jpg" width="400" height="400" />|
  
| Đặc điểm kỹ thuật | Thông số |
|:---|:---|
|Tần số hoạt động của CPU | 240 MHz (*)|
|Tần số cấp cho khối APB| 80 MHz(**) |
|Điện áp hoạt động | 1.8 ~ 3.6 VDC |
|Dòng điện định mức | 68 ~ 310 mA |
|Cổng kết nối + cấp nguồn| USB type C|

</div>
(*) : Có thể chỉnh thành các giá trị 80, 160, 240 MHz. Mặc định (nếu lập trình trên Aurduino IDE hoặc PlaformIO) là 240 MHz.
<br />(**): Mặc định (nếu lập trình trên Aurduino IDE hoặc PlaformIO) là 80 MHz.


### Các chức năng có thể dùng được trên bảng mạch WEMOS ESP32-S2 Mini
|Chức năng|Tên khối|Ghi chú|
|:---|:---|:---|
|GPIO|1-14, 15-18, 33-40| tối đa 27 GPIOs|
|RTC GPIO|1-14||
|ADC|ADC1; ADC2|Mỗi bộ có 10 kênh|
|DAC|DAC1; DAC2|Mỗi bộ có 1 kênh |
|UART|UART1|UART0 không đấu chân ra vì dùng cho cổng USB.<br />Nếu dùng SoftwareSerial.h, bạn có thể thiết lập 2 chân GPIO "trống" bất kỳ nào làm Tx và Rx|
|SPI|MISO(SDO), MOSI(SDI), SCK(SCLK), SS|Nếu dùng SoftSPI.h, bạn có thể thiết lập 4 chân GPIO "trống" bất kỳ nào làm 4 chân của SPI * Not confirm|
|I2C|||
|Chân cảm biến chạm (Touch pins)|||
|PWM||Tần số mặc định: 1 kHz. Nếu dùng ledcSetup() thì có thể chỉnh tần số PWM lên tới 40 MHz|
|USB|||
|RF|WiFi|Không có Bluetooth|

### Pinout map
![ESP32-S2 Mini Pinout](/images/ESP32S2MiniPinoutVer2.jpg)

## Lưu ý khi kích hoạt chức năng WiFi
Khi đã kích hoạt chức năng WiFi trên ESP32 S2 thì bộ ADC2 sẽ không thể sử dụng được nữa.
> Vì mô-đun ADC2 cũng được Wi-Fi sử dụng nên hoạt động đọc của `adc2_get_raw()` có thể không thành công khi chương trình đang thực thi giữa `esp_wifi_start()` và `esp_wifi_stop()` (Trích [nguồn tham khảo 3](#Nguồn-tham-khảo))

## Thiết lập môi trường lập trình
### Dùng PlatformIO trên VS Code
Tạo project
  - Chọn tên Board: WEMOS LOLIN S2 


### Dùng ArduinoIDE


## Code, nạp code và kết quả
### [Không bắt buộc] Lấy địa chỉ MAC của board ESP32

> Code lấy địa chỉ MAC của board ESP32 mình để ở [đây].

### Lập trình board ESP32 gửi gói tin ESP-NOW

> Code lập trình board ESP32 gửi gói tin ESP-NOW mình để ở [đây].

### Lập trình board ESP32 nhận gói tin ESP-NOW

> Code lập trình board ESP32 nhận gói tin ESP-NOW mình để ở [đây].

### Nạp code, kết quả

## Video Youtube

## Nguồn tham khảo
1. [S2 mini - WEMOS * not an actual reference](https://www.wemos.cc/en/latest/s2/s2_mini.html)
2. [ESP32S2Mini_OnOffLED-Example - (Me)Electricalthinking29 * not an actual reference](https://github.com/ElectricalThinking29/ESP32S2Mini_OnOffLED-Example/tree/main)
3. [Analog to Digital Converter (ADC) - Espressif Systems (Shanghai) Co., Ltd * not an actual reference](https://docs.espressif.com/projects/esp-idf/en/v4.4.1/esp32s2/api-reference/peripherals/adc.html)
4. [ESP32 S2 Mini * not an actual reference](https://www.sudo.is/docs/esphome/boards/esp32s2mini/)
5. [ESP32-S2 Series datasheet - Espressif Systems (Shanghai) Co., Ltd](https://www.espressif.com/sites/default/files/documentation/esp32-s2_datasheet_en.pdf)
