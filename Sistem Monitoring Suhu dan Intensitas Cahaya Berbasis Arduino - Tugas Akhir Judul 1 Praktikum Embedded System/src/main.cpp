#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT22
#define LDRPIN A0
#define LED_PIN 6
#define BUZZ_PIN 7

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();

  String pesan = "Kanaya Traylingga Pratama - 2415061059    ";
  for (int i = 0; i < pesan.length(); i++)
  {
    lcd.setCursor(0, 0);
    lcd.print("Tugas Akhir:");
    lcd.setCursor(0, 1);
    lcd.print(pesan.substring(i, i + 16));
    delay(300);
  }
  lcd.clear();
}

void loop()
{
  float suhu = dht.readTemperature();
  int cahaya = analogRead(LDRPIN);

  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhu);
  lcd.print(" C  ");
  if (suhu > 30.0)
  {
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Suhu Negatif   ");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Suhu Positif  ");
  }
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Cahaya: ");
  lcd.print(cahaya);
  if (cahaya < 200)
  {
    tone(BUZZ_PIN, 1000);
    lcd.setCursor(0, 1);
    lcd.print("Status: GELAP   ");
  }
  else
  {
    noTone(BUZZ_PIN);
    lcd.setCursor(0, 1);
    lcd.print("Status: TERANG  ");
  }
  delay(2000);
  lcd.clear();
}