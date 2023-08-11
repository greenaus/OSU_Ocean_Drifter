#include "max6675.h"

int sckPin = 52;
int csPin = 13;
int soPin = 50;

MAX6675 thermocouple(sckPin, csPin, soPin);

void setup() {   
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  float temperature = thermocouple.readCelsius();
  Serial.println(temperature);
  delay(1000);
}
