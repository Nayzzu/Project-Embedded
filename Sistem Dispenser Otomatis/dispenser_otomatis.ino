#define TRIG_PIN 7
#define ECHO_PIN 9
#define RELAY_PIN 13
#define LED_PIN 2

#define JARAK_MIN 1
#define JARAK_MAX 5

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Kondisi awal
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF (active LOW)
  digitalWrite(LED_PIN, LOW);

  Serial.println("Dispenser Otomatis Siap");
}

void loop() {

  distance = bacaJarak();

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance >= JARAK_MIN && distance <= JARAK_MAX) {

    digitalWrite(RELAY_PIN, LOW); // Pompa ON
    digitalWrite(LED_PIN, HIGH);  // LED ON

    Serial.println("Pompa ON");

  } else {

    digitalWrite(RELAY_PIN, HIGH); // Pompa OFF
    digitalWrite(LED_PIN, LOW);    // LED OFF

    Serial.println("Pompa OFF");
  }

  delay(300);
}

float bacaJarak() {

  float total = 0;
  int jumlahData = 0;

  for (int i = 0; i < 5; i++) {

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration > 0) {
      total += duration * 0.034 / 2;
      jumlahData++;
    }

    delay(10);
  }

  if (jumlahData == 0) {
    return 999;
  }

  return total / jumlahData;
}