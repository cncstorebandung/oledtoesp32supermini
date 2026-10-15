#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===============================
// OLED ESP32-C3 SUPERMINI
// ===============================

#define SDA_PIN 8
#define SCL_PIN 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

uint8_t oledAddress = 0x3C;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32-C3 OLED TEST");

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  // Cek alamat OLED
  Wire.beginTransmission(0x3C);

  if (Wire.endTransmission() == 0) {
    oledAddress = 0x3C;
    Serial.println("OLED ditemukan: 0x3C");
  } else {
    Wire.beginTransmission(0x3D);

    if (Wire.endTransmission() == 0) {
      oledAddress = 0x3D;
      Serial.println("OLED ditemukan: 0x3D");
    } else {
      Serial.println("OLED TIDAK TERDETEKSI!");
      Serial.println("Cek kabel SDA, SCL, VCC, GND");

      while (true) {
        delay(1000);
      }
    }
  }

  if (!display.begin(
      SSD1306_SWITCHCAPVCC,
      oledAddress
  )) {
    Serial.println("Gagal inisialisasi OLED!");

    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("CNC STORE BANDUNG");
  display.println("ESP32-C3 SUPERMINI");
  display.println("OLED READY!");

  display.display();
  delay(2000);
}

void loop() {
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);

  display.setCursor(0, 0);
  display.println("Temp:");

  display.setCursor(0, 18);
  display.println("25.4 C");

  display.display();
  delay(1000);
}