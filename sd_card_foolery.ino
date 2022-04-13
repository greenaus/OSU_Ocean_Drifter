#include <SPI.h>
#include <SD.h>

File myFile;

String first_name = "";
String last_name = "";
String major = "";

void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");
  
  Serial.println("Input first name: ");
  while (Serial.available() == 0) {}
  first_name = Serial.readString();
  Serial.println("Input last name: ");
  while (Serial.available() == 0) {}
  last_name = Serial.readString();
  Serial.println("Input major: ");
  while (Serial.available() == 0) {}
  major = Serial.readString();
  
  myFile = SD.open("test.txt");
  if (myFile.available()) {
    SD.remove("test.txt");
    Serial.println("Removed existing file from SD card.");
  }
  myFile.close();

  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to file...");
    myFile.println("First name: " + first_name);
    myFile.println("Last name: " + last_name);
    myFile.println("Major: " + major);
    myFile.close();
    Serial.println("Done!");
  }
  else {
    Serial.println("Error opening file.");
  }
}

void loop() {}
