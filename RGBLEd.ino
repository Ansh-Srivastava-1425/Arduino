const int PIN_RED   = 4;
const int PIN_GREEN = 5;
const int PIN_BLUE  = 6;
void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
}
void loop() {
  // color code #00C9CC (R = 0,   G = 201, B = 204)
  setColor(0, 201, 204);
  delay(1000); // keep the color 1 second
  // color code #F7788A (R = 247, G = 120, B = 138)
  setColor(247, 120, 138);
  delay(1000); // keep the color 1 second
  // color code #34A853 (R = 52,  G = 168, B = 83)
  setColor(52, 168, 83);
  delay(1000); // keep the color 1 second
}
void setColor(int R, int G, int B) {
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  B);
}