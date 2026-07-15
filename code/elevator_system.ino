#include "HX711.h"
#include <LiquidCrystal_I2C.h>

#define DT 3
#define SCK 2

HX711 scale;
LiquidCrystal_I2C lcd(0x27,16,2);

const int motorPin = 8;
const int buzzerPin = 9;

float weight;
float maxWeight = 1000.0;

void setup() {
  Serial.begin(9600);

  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(motorPin, LOW);
  digitalWrite(buzzerPin, LOW);

  lcd.init();
  lcd.backlight();

  scale.begin(DT, SCK);
  scale.set_scale();
  scale.tare();

  lcd.setCursor(0,0);
  lcd.print("Elevator");
  lcd.setCursor(0,1);
  lcd.print("Initializing");
  delay(2000);
  lcd.clear();
}

void loop() {

  weight = scale.get_units(10);

  lcd.setCursor(0,0);
  lcd.print("Weight:");
  lcd.print(weight);
  lcd.print("g ");

  if(weight > maxWeight){

    digitalWrite(motorPin, LOW);
    digitalWrite(buzzerPin, HIGH);

    lcd.setCursor(0,1);
    lcd.print("OVERLOAD     ");

  }
  else{

    digitalWrite(motorPin, HIGH);
    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0,1);
    lcd.print("Moving       ");

  }

  delay(500);
}
