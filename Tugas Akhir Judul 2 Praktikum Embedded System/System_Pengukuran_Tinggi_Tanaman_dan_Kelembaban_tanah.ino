#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int soilPin = A0;
byte plantHeight = 0;
int soil = 0;

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  soil = analogRead(soilPin) / 4;

  Wire.requestFrom(8, 1);
  if (Wire.available()) {
    plantHeight = Wire.read();
  }

  lcd.setCursor(0, 0);
  lcd.print("Tinggi:");
  lcd.print(plantHeight);
  lcd.print("cm   ");

  lcd.setCursor(0, 1);
  lcd.print("Soil:");
  lcd.print(soil);
  lcd.print("     ");

  delay(500);
}