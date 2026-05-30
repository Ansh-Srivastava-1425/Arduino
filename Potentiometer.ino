const int potPin = A0;
const int buzzerPin = 9;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);  // 0 to 1023

  int frequency = map(potValue, 0, 1023, 100, 2000);

  tone(buzzerPin, frequency);

  delay(10);
}