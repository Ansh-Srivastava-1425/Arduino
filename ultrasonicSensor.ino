int trigg = 7;
int echo = 6;
long timeInmicro;
int distanceInCm;

void setup() {
  pinMode(trigg, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigg, LOW);
  delayMicroseconds(2);

  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigg, LOW);

  timeInmicro = pulseIn(echo, HIGH);

  distanceInCm = timeInmicro / 29 / 2;

  Serial.print("Distance: ");
  Serial.print(distanceInCm);
  Serial.println(" cm");

  delay(100);
}