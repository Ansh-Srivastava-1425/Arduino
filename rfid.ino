#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

#define RED_LED 2
#define GREEN_LED 3
#define BUZZER 5
#define SERVO_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

int serialNumber = 1;

struct Student {
  String uid;
  String roll;
  String name;
};

Student students[] = {
  {"91400407", "HST-01", "Harsh"},
  {"e49fba06", "HST-02", "Viraj"},
  {"xxxxxxxx", "HST-03", "Student3"},
  {"xxxxxxxx", "HST-04", "Student4"}
};

const int totalStudents = sizeof(students) / sizeof(students[0]);

int findStudent(String uid) {
  for (int i = 0; i < totalStudents; i++) {
    if (students[i].uid.equalsIgnoreCase(uid))
      return i;
  }
  return -1;
}

void openDoor() {
  doorServo.write(90);   // open position
  delay(3000);           // keep open 3 seconds
  doorServo.write(0);    // close position
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GARAGE  DOOR");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  Serial.println("Garage Door System Started");
  Serial.println("S.No,UID,Roll,Name,Status");

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan Card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10)
      uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toLowerCase();

  int index = findStudent(uid);
  lcd.clear();

  if (index != -1) {

    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER, 1000);
    delay(200);
    noTone(BUZZER);

    Serial.print(serialNumber++);
    Serial.print(",");
    Serial.print(uid);
    Serial.print(",");
    Serial.print(students[index].roll);
    Serial.print(",");
    Serial.print(students[index].name);
    Serial.println(",OPENED");

    lcd.setCursor(0, 0);
    lcd.print("Welcome!");
    lcd.setCursor(0, 1);
    lcd.print("Door Opening...");

    openDoor();

    delay(1500);
    digitalWrite(GREEN_LED, LOW);

  } else {

    for (int i = 0; i < 3; i++) {
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 500);
      delay(200);
      noTone(BUZZER);
      digitalWrite(RED_LED, LOW);
      delay(200);
    }

    Serial.print(serialNumber++);
    Serial.print(",");
    Serial.print(uid);
    Serial.println(",Unknown,Unknown,UNREGISTERED");

    lcd.setCursor(0, 0);
    lcd.print("Unknown Card");
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan Card...");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}