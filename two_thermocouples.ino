#include "max6675.h"

int sckPin = 52;
int soPin = 50;
int cs1Pin = 13;
int cs2Pin = 12;

MAX6675 thermocouple1(sckPin, cs1Pin, soPin);
MAX6675 thermocouple2(sckPin, cs2Pin, soPin);

void setup() {   
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  float temperature1 = thermocouple1.readCelsius();
  float temperature2 = thermocouple2.readCelsius();
  Serial.print("Temperature 1: ");
  Serial.println(temperature1);
  Serial.print("Temperature 2: ");
  Serial.println(temperature2);
  delay(1000);
}
