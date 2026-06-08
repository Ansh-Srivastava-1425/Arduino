#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const String password = "1234";
String input = "";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int buzzer = 11;

void keyBeep() {
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
}

void correctBeep() {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}

void wrongBeep() {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

void setup() {
  pinMode(buzzer, OUTPUT);

  myServo.attach(10);
  myServo.write(90);   // Locked

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    keyBeep();

    if (key == '#') {

      if (input == password) {

        lcd.clear();
        lcd.print("Access Granted");

        correctBeep();

        myServo.write(0);   // Unlock

        delay(5000);

        myServo.write(90);  // Lock again

      } else {

        lcd.clear();
        lcd.print("Wrong Password");

        wrongBeep();

        delay(2000);
      }

      input = "";

      lcd.clear();
      lcd.print("Enter Password");
    }

    else if (key == '*') {

      input = "";

      lcd.clear();
      lcd.print("Cleared");

      delay(1000);

      lcd.clear();
      lcd.print("Enter Password");
    }

    else {

      input += key;

      lcd.setCursor(input.length() - 1, 1);
      lcd.print('*');
    }
  }
}