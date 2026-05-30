#include <Servo.h>

Servo s1;

int pot = A0;
int x;
int value;

void setup() {
  pinMode(pot, INPUT);  
  s1.attach(9);
}

void loop() {
  x = analogRead(pot);
  value = map(x, 0, 1023, 0, 180);

  s1.write(value);
}