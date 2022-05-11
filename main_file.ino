#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_MAX31856.h>

//SD Card Module: CS: 10, SCK: 13, MOSI: 11, MISO: 12
//Thermocouple Module: SCK: 8, SDO: 7, SDI: 6, CS: 5
//GPS Module: RX: 4, TX: 3

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

int count = 0;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(TXPin, RXPin);

// The file
File myFile;

// Thermocouple initialization
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(5, 6, 7, 8);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");
  Serial.println();

  if (SD.exists("gps_data.txt")) SD.remove("gps_data.txt");

  while (!Serial) delay(10);
  Serial.println("MAX31856 thermocouple initialized");
  Serial.println();
  maxthermo.begin();
  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

ISR(TIMER1_COMPA_vect) {
  count++;
}

void loop() {
  if (count == 10) {
    while (ss.available() > 0){
      gps.encode(ss.read());
      if (gps.location.isUpdated()){
        Serial.print("Latitude: "); 
        Serial.print(gps.location.lat(), 6);
        Serial.print(", Longitude: "); 
        Serial.println(gps.location.lng(), 6);
        Serial.print("Hour: ");
        Serial.print(gps.time.hour());
        Serial.print(", Minute: ");
        Serial.print(gps.time.minute());
        Serial.print(", Second: ");
        Serial.println(gps.time.second());
        Serial.print("Cold Junction Temperature: ");
        Serial.println(maxthermo.readCJTemperature());
        Serial.print("Thermocouple Temperature: ");
        Serial.println(maxthermo.readThermocoupleTemperature());
        Serial.println();
  
        myFile = SD.open("gps_data.txt", FILE_WRITE);
        myFile.seek(EOF);
        myFile.print("Latitude: "); 
        myFile.print(gps.location.lat(), 6);
        myFile.print(", Longitude: "); 
        myFile.println(gps.location.lng(), 6);
        myFile.print("Hour: ");
        myFile.print(gps.time.hour());
        myFile.print(", Minute: ");
        myFile.print(gps.time.minute());
        myFile.print(", Second: ");
        myFile.println(gps.time.second());
        myFile.print("Cold Junction Temperature: ");
        myFile.println(maxthermo.readCJTemperature());
        myFile.print("Thermocouple Temperature: ");
        myFile.println(maxthermo.readThermocoupleTemperature());
        myFile.println();
        myFile.close();

        count = 1;
      }
    }
  }
}
