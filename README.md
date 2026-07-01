# ESP32 IR Thermometer with OLED Display

A project that reads object and ambient temperature from a non-contact infrared sensor and displays live readings on a built-in OLED screen.

---

## Hardware

- ESP32 development board with integrated 0.96" 128×64 OLED (WiFi + Bluetooth, CP2102, Xtensa LX6)
- GY-906 breakout board (MLX90614 infrared temperature sensor)
- Jumper wires

---

---

## Troubleshooting

**OLED stays blank or frozen**
The board may need the OLED reset pin toggled or has different I2C pins. Run the I2C scanner to confirm `0x3C` is visible. If nothing is found, the board's SDA/SCL differ from GPIO5/GPIO4 — try other pin combinations.

**"MLX90614 not found" on serial monitor**
- Confirm GY-906 pin order — some boards label left to right as VIN, GND, **SCL, SDA** (not SDA, SCL)
- Measure voltage on the GY-906's VIN and GND pins with a multimeter. 0V means the connection is faulty even if it looks plugged in — replace the wire or pin.

**Upload fails: "Wrong boot mode detected (0x17)"**
Hold **BOOT** during upload, release after "Connecting..." appears.

**Upload fails: "chip stopped responding"**
Try a different USB cable. Many cables are charge-only with no data lines.

**Garbled output in serial monitor**
Set baud rate to `115200` — add `monitor_speed = 115200` to `platformio.ini` to make it permanent.

---
