#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

//gps: rx = 4, tx = 3
//sd card: cs = 10, sck = 13, mosi = 10, mosi = 12 

float latitude = 0, longitude = 0;

File myFile;
SoftwareSerial gpsSerial(4,3);
TinyGPS gps;

void setup(){

  Serial.begin(9600);
  gpsSerial.begin(9600);
  
  Serial.println("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");
 
}

void loop(){
  while (gpsSerial.available()){
    if (gps.encode(gpsSerial.read())) {
      gps.f_get_position(&latitude,&longitude);
      myFile = SD.open("gps_data.txt", FILE_WRITE);
      myFile.seek(EOF);
      myFile.print("Latitude: "); 
      myFile.println(latitude, 6);
      myFile.print("Longitude: "); 
      myFile.println(longitude, 6);
      myFile.println();
      myFile.close();
      delay(10000);
    }
  }
}
