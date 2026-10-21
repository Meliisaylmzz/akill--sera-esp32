#include <DHT.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 15
#define DHTTYPE DHT22
#define SERVO_PIN 18
#define LED_PIN 4

const float ESIK = 30.0;  // Bu sıcaklıktan sonra pencere açılır

DHT dht(DHTPIN, DHTTYPE);
Servo pencere;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pencere.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  lcd.init();
  lcd.backlight();
  pencere.write(0);
  Serial.println("sicaklik,nem,pencere");
}

void loop() {
  float sicaklik = dht.readTemperature();
  float nem = dht.readHumidity();

  if (isnan(sicaklik) || isnan(nem)) {
    Serial.println("Sensor okunamadi");
    delay(2000);
    return;
  }

  bool acik = sicaklik > ESIK;

  if (acik) {
    pencere.write(90);
    digitalWrite(LED_PIN, HIGH);
  } else {
    pencere.write(0);
    digitalWrite(LED_PIN, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(sicaklik, 1);
  lcd.print("C N:%");
  lcd.print(nem, 0);
  lcd.print("  ");

  lcd.setCursor(0, 1);
  lcd.print(acik ? "Pencere: ACIK   " : "Pencere: KAPALI ");

  Serial.print(sicaklik);
  Serial.print(",");
  Serial.print(nem);
  Serial.print(",");
  Serial.println(acik ? 1 : 0);

  delay(2000);
}