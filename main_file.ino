#include <TinyGPS++.h>
#include <SD.h>
#include <SPI.h>
#include "max6675.h"

int sckPin = 52;
int soPin = 50;
int cs1Pin = 13;
int cs2Pin = 12;

MAX6675 thermocouple1(sckPin, cs1Pin, soPin);
MAX6675 thermocouple2(sckPin, cs2Pin, soPin);
TinyGPSPlus gps;
File myFile;

int count = 0;
double latitude = 0;
double longitude = 0;
double hours = 0;
double minutes = 0;
double seconds = 0;
float temp1_celsius = 0;
float temp2_celsius = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  //SD card initialization
  Serial.println("Initializing SD card...");
  if (!SD.begin(53)) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");
  Serial.println();
  
  if (SD.exists("data.txt")) SD.remove("data.txt"); //if there's already a file, delete it

  //timer/counter1 initialization
  cli(); //stop interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624; // 1 Hz
  TCCR1B |= (1 << WGM12); //ctc mode
  TCCR1B |= (1 << CS12) | (1 << CS10); //prescaler
  TIMSK1 |= (1 << OCIE1A);
  sei(); //start interrupts
}

ISR(TIMER1_COMPA_vect) {
  count++; //increment count
}

void loop() {
  if (count == 5) {
    while (Serial1.available()) {
      gps.encode(Serial1.read());
      if (gps.location.isUpdated()) {
        latitude = gps.location.lat(), 6;
        longitude = gps.location.lng(), 6;
        hours = gps.time.hour();
        minutes = gps.time.minute();
        seconds = gps.time.second();
        temp1_celsius = thermocouple1.readCelsius();
        temp2_celsius = thermocouple2.readCelsius();

        Serial.print("Latitude: "); 
        Serial.print(latitude);
        Serial.print(", Longitude: "); 
        Serial.println(longitude);
        Serial.print("Hour: ");
        Serial.print(hours);
        Serial.print(", Minute: ");
        Serial.print(minutes);
        Serial.print(", Second: ");
        Serial.println(seconds);

        Serial.print("Thermocouple 1 Temperature: ");
        Serial.println(temp1_celsius);
        Serial.print("Thermocouple 2 Temperature: ");
        Serial.println(temp2_celsius);

        Serial.println();

        myFile = SD.open("data.txt", FILE_WRITE);
        myFile.seek(EOF);

        myFile.print("Latitude: "); 
        myFile.print(latitude);
        myFile.print(", Longitude: "); 
        myFile.println(longitude);
        myFile.print("Hour: ");
        myFile.print(hours);
        myFile.print(", Minute: ");
        myFile.print(minutes);
        myFile.print(", Second: ");
        myFile.println(seconds);

        myFile.print("Thermocouple 1 Temperature: ");
        myFile.println(temp1_celsius);
        myFile.print("Thermocouple 2 Temperature: ");
        myFile.println(temp2_celsius);

        myFile.println();
        
        myFile.close();

        count = 0;
      }
    }
  }
  if (count > 5) count = 0;
}
