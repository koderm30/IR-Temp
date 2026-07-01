#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1
#define OLED_ADDRESS  0x3C

#define SDA_PIN  5
#define SCL_PIN  4

#define READ_INTERVAL_MS 500

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MLX90614 mlx;

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("SSD1306 not found – check wiring!");
    while (true) delay(1000);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Initialising...");
  display.display();

  if (!mlx.begin()) {
    Serial.println("MLX90614 not found – check wiring!");
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println("IR sensor error!");
    display.display();
    while (true) delay(1000);
  }

  delay(500);
}

void loop() {
  float ambientC = mlx.readAmbientTempC();
  float objectC  = mlx.readObjectTempC();

  Serial.printf("Ambient: %.1f C  |  Object: %.1f C\n", ambientC, objectC);

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(22, 0);
  display.println("IR Thermometer");
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  // Object temp – large, centred
  display.setTextSize(2);
  char buf[12];
  dtostrf(objectC, 5, 1, buf);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2 - 8, 20);
  display.print(buf);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH + w) / 2 - 12, 22);
  display.println(" \xF8""C");

  // Ambient footer
  display.drawLine(0, 50, 127, 50, SSD1306_WHITE);
  display.setCursor(0, 55);
  display.print("Ambient: ");
  char bufA[8];
  dtostrf(ambientC, 4, 1, bufA);
  display.print(bufA);
  display.println(" \xF8""C");

  display.display();
  delay(READ_INTERVAL_MS);
}