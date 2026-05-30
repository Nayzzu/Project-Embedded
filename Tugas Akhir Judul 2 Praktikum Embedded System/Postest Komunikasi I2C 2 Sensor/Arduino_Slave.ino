#include <Wire.h>

#define trigPin 9
#define echoPin 10

int sensorPin = A0; // Pin analog untuk sensor kelembapan tanah
int ledPin = 13;    // Pin untuk LED indikator (optional)
long duration;
int distance;

// Menyimpan nilai kelembapan yang terdeteksi
int moistureLevel = 0;

// Nilai ambang batas kelembapan tanah (misalnya 400 untuk tanah kering)
int moistureThreshold = 400;

void setup() {
  // Inisialisasi pin
  pinMode(ledPin, OUTPUT);     // Menetapkan pin LED sebagai OUTPUT         // Memulai komunikasi serial untuk debugging
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // Membaca nilai kelembapan tanah dari sensor
  moistureLevel = analogRead(sensorPin);

   // Bersihkan pin Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Kirim sinyal trigger 10µs
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca durasi sinyal Echo
  duration = pulseIn(echoPin, HIGH);

  // Hitung jarak
  distance = (duration * 0.0343) / 2;
 
  
  delay(1000);  // Tunggu 1 detik sebelum membaca ulang
}

void receiveEvent (int bytes) {
  String message = "";
  while (Wire.available()){
    char c = Wire.read();
    message += c;
  }
  Serial.println("Message received: " + message);
  if (message == "1"){
   // Menampilkan nilai kelembapan di Serial Monitor (untuk debugging)
  Serial.print("Kelembapan Tanah: ");
  Serial.println(moistureLevel);
  } else {
    // Tampilkan di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  }
}