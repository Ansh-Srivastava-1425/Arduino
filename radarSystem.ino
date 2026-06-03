#include <Servo.h>

const int trigPin = 10;
const int echoPin = 8;

const int greenLED = 3;
const int redLED = 4;
const int buzzer = 5;

long duration;
int distance;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  myServo.attach(12);
}

void loop() {

  // Scan left to right
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);

    distance = calculateDistance();

    updateIndicators();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  // Scan right to left
  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);

    distance = calculateDistance();

    updateIndicators();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

void updateIndicators() {

  if (distance <= 20) {

    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    // Radar warning double beep
    tone(buzzer, 2200);
    delay(50);
    noTone(buzzer);
    delay(30);

    tone(buzzer, 2200);
    delay(50);
    noTone(buzzer);
  }
  else {

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);

    noTone(buzzer);
  }
}

int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}