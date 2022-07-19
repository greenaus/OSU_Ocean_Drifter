#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  
  Serial.println("Initializing SD card...");
  if (!SD.begin(53)) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");
  
  myFile = SD.open("data.txt");
  if (myFile.available()) {
    SD.remove("data.txt");
    Serial.println("Removed existing file from SD card.");
  }
  myFile.close();

  myFile = SD.open("data.txt", FILE_WRITE);
  
  if (myFile) {
    myFile.print("Hello there!");
    Serial.println("Success");
  }
  else {
    Serial.println("Failure");
  }
  myFile.close();  
}

void loop() {}
