#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
int soilPin = A0;
int pumpPin = 8;
int weatherPin = 7;   // Slide switch for weather (RAIN / NO RAIN)

// Threshold
int soilThreshold = 400;  // Adjust based on calibration

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(weatherPin, INPUT);

  lcd.begin(16, 2);
  lcd.print("Smart Irrigation");
  delay(2000);
  lcd.clear();
}

void loop() {
  int soilValue = analogRead(soilPin);
  int weatherState = digitalRead(weatherPin); // HIGH = Rain

  // Display soil value
  lcd.setCursor(0, 0);
  lcd.print("moisture:");
  lcd.print(soilValue);
  lcd.print("   ");

  // WEATHER CHECK FIRST
  if (weatherState == HIGH) {
    // Rain condition
    digitalWrite(pumpPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Rain Detected ");
  }
  else {
    // No rain → Check soil
    if (soilValue < soilThreshold) {
      digitalWrite(pumpPin, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Pump: ON      ");
    } 
    else {
      digitalWrite(pumpPin, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Pump: OFF     ");
    }
  }

  delay(1000);
}