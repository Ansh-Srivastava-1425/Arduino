#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gate;

const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 2;

long duration;
int distance;

bool gateOpen = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  gate.attach(servoPin);
  gate.write(90); // closed

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  delay(2000);
  lcd.clear();
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms

  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

void loop() {

  distance = getDistance();

  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  if (distance > 0 && distance <= 15 && !gateOpen) {

    gateOpen = true;

    lcd.setCursor(0, 1);
    lcd.print("Gate Opening ");

    gate.write(180);
    delay(5000);

    gate.write(90);

    lcd.setCursor(0, 1);
    lcd.print("Gate Closed  ");

    delay(1000);
  }

  if (distance > 20) {
    gateOpen = false; // reset when car leaves
  }

  if (distance == -1) {
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error ");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Waiting Car  ");
  }

  delay(200);
}