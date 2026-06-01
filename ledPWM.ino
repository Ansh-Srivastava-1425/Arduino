int led = 11;
int pot = A0;
int x , y;

void setup() {
  pinMode(led , OUTPUT);
  pinMode(pot , INPUT);
}

void loop() {
  x = analogRead(A0);
  y = map(x,0,1023,0,255);
  analogWrite(led , y);
  }
