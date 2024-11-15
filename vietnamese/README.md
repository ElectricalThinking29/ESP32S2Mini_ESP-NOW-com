# Lập trình bảng mạch ESP32-S2 mini giao tiếp qua WiFi dùng giao thức ESP-NOW

## Tổng quan
- Bài viết sẽ trình bày về:
  - Các chức năng có thể dùng được trên bảng mạch ESP32-S2 mini
  - Điều cần lưu ý khi sử dụng chức năng WiFi của ESP32-S2.
  - Thiết lập môi trường để lập trình board ESP32-S2 mini
  - Code, nạp code, kết quả đạt được.
 
## Về bảng mạch ESP32-S2 mini
- Ảnh chụp 2 mặt của board
- Đặc điểm kỹ thuật:
  - Tần số hoạt động   : 240 MHz <sup>(Đây là tần số sau bộ chia tần số cao, tần số hoạt động thực tế cấp cho các ngoại vi sẽ thấp hơn nhiều)</sup>
  - Điện áp hoạt động  : 3.3 VDC
  - Kết nối + cấp nguồn qua cổng USB type C
  - 
- Các chức năng có thể dùng được trên bảng mạch WEMOS ESP32-S2 Mini
  - GPIO    : có thể dùng tới 27 chân GPIO: GPIO 1-14, 15-18, 33-40
  - RTC GPIO:
  - ADC     :
  - DAC     :
  - UART    :
  - SPI     :
  - I2C     :
  - Cảm biến điện dung:
  - PWM     :

- Pinout map:
![ESP32-S2 Mini Pinout](https://github.com/ElectricalThinking29/ESP32S2Mini_OnOffLED-Example/tree/main/ESP32S2MiniPinoutVer2.jpg?raw=true)

## Lưu ý khi kích hoạt chức năng WiFi
- Mất bộ ADC nào -> Các chân nào sẽ không dùng chức năng ADC được nữa

## Thiết lập môi trường lập trình
### Dùng PlatformIO trên VS Code

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
1. [S2 mini - WEMOS](https://www.wemos.cc/en/latest/s2/s2_mini.html)
2. [ESP32S2Mini_OnOffLED-Example - (Me)Electricalthinking29](https://github.com/ElectricalThinking29/ESP32S2Mini_OnOffLED-Example/tree/main)
