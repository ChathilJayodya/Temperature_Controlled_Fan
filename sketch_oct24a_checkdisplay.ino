#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2          // DHT22 signal pin connected to D2
#define DHTTYPE DHT22

#define IN1 8             // Motor driver input 1
#define IN2 9             // Motor driver input 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  lcd.setCursor(0,0);
  lcd.print("Temp Ctrl Fan");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Celsius

  // Check if reading failed
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    delay(2000);
    return;
  }

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1);
  lcd.print((char)223); // degree symbol
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h, 0);
  lcd.print("%    ");

  // Control fan
  if (t > 30) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    lcd.setCursor(12, 0);
    lcd.print("ON ");
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    lcd.setCursor(12, 0);
    lcd.print("OFF");
  }

  delay(1000);
}
