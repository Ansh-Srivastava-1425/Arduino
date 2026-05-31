#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  lcd.init();
  lcd.backlight();

  dht.begin();


  lcd.setCursor(0, 0);
  lcd.print("DHT11 Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    lcd.clear();
    lcd.print("Sensor Error");
    delay(2000);
    return;
  }

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); // degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(hum);
  lcd.print("%");

  delay(2000);
}