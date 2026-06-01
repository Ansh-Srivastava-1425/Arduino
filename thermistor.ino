// Thermistor parameters
#define RT0 10000     // Resistance at 25°C
#define B 3977        // Beta coefficient
#define R 10000       // Series resistor (10kΩ)

float RT, VR, lnVal, TX, T0, VRT;
int adcValue;

void setup() {
  Serial.begin(9600);
  T0 = 25 + 273.15;  // Convert 25°C to Kelvin
}

void loop() {

  // Read ADC value
  adcValue = analogRead(A0);

  // Convert ADC to voltage
  VRT = (5.0 * adcValue) / 1023.0;

  // Prevent division by zero
  if (VRT <= 0.01 || VRT >= 4.99) {
    Serial.print("ADC: ");
    Serial.print(adcValue);
    Serial.println("  -> Check wiring!");
    delay(1000);
    return;
  }

  // Voltage across resistor
  VR = 5.0 - VRT;

  // Thermistor resistance
  RT = VRT / (VR / R);

  // Beta equation
  lnVal = log(RT / RT0);
  TX = 1.0 / ((lnVal / B) + (1.0 / T0));

  // Kelvin to Celsius
  TX = TX - 273.15;

  Serial.print("ADC: ");
  Serial.print(adcValue);

  Serial.print("  Temperature: ");
  Serial.print(TX);
  Serial.print(" C");

  Serial.print("  ");
  Serial.print(TX + 273.15);
  Serial.print(" K");

  Serial.print("  ");
  Serial.print((TX * 1.8) + 32);
  Serial.println(" F");

  delay(1000);
}