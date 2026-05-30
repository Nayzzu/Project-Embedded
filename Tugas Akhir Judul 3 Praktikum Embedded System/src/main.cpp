#define BLYNK_TEMPLATE_ID "TMPL6lDDnXazd"
#define BLYNK_TEMPLATE_NAME "TUGAS AKHIR JUDUL 3 EMBEDDED SYSTEM"
#define BLYNK_AUTH_TOKEN "BrjlyH2dWpYBejobd2K-3kPMvqs2LbLT"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Konfigurasi Pin
#define LDR_PIN 34
#define SERVO_PIN 18

Servo myservo;
char auth[] = "BrjlyH2dWpYBejobd2K-3kPMvqs2LbLT";
char ssid[] = "Wokwi-GUEST"; // Default Wokwi WiFi
char pass[] = "";

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi Servo
  myservo.attach(SERVO_PIN);
  
  // Koneksi Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  
  int ldrValue = analogRead(LDR_PIN);
  // Konversi nilai ADC (0-4095) ke Persentase (0-100)
  int luxPercent = map(ldrValue, 4095, 0, 0, 100); 

  // Kirim data ke Blynk
  Blynk.virtualWrite(V1, luxPercent);

  // Logika Aktuator Servo
  // Jika gelap (lux < 30%), Servo bergerak ke 90 derajat
  if (luxPercent < 30) {
    myservo.write(90);
    Blynk.virtualWrite(V2, 255); // Nyalakan LED di Blynk
  } else {
    myservo.write(0);
    Blynk.virtualWrite(V2, 0);   // Matikan LED di Blynk
  }

  // --- TAMBAHAN SERIAL MONITOR ---
  Serial.print("LDR Raw: ");
  Serial.print(ldrValue);
  Serial.print(" | Kecerahan: ");
  Serial.print(luxPercent);
  Serial.print("% | Status Servo: ");
  if (luxPercent < 30)
  {
    Serial.println("90 Derajat (Gelap)");
  }
  else
  {
    Serial.println("0 Derajat (Terang)");
  }
  // --------------------------------

  delay(500);
}