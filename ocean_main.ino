//libraries/files included
#include <TinyGPS++.h>
#include <SD.h>
#include <SPI.h>
#include <MAX6675.h>

//pin assignments
#define CS_PIN1 13
#define CS_PIN2 12
#define soPin = 50;
#define sckPin = 52;

//thermocouple initialization
MAX6675 tcouple1(CS_PIN1);
MAX6675 tcouple2(CS_PIN2);

File myFile; //file object
TinyGPSPlus gps;//gps object

//data variables
int count = 0;
double latitude = 0;
double longitude = 0;
double hours = 0;
double minutes = 0;
double seconds = 0;
double temperature1 = 0;
double temperature2 = 0;
char myFileName[] = "test1.txt";

void setup() {
  //initialize serial
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
  
 //check the files name and creat a new file
  for (int i = 1; i < 1000; i++) {
  char y = i+'0';
  myFileName[4] = y; // change the file name: test1.txt test2.txt.......
  
  if (SD.exists(myFileName)){ // if the file already exist
    continue;
    }
 
    Serial.println(myFileName); // Print the filename to which data is written before each run. 
    break;
  }

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

ISR(TIMER1_COMPA_vect) { //interrupt function to be called when timer reaches max
  count++; //increment count
}

void loop() {
  //run the part every 5 second.
  if (count == 5) {
    while (Serial1.available()) {
      gps.encode(Serial1.read());
      if (gps.location.isUpdated()) {
        
        latitude = gps.location.lat(), 6; //get latitude reading with up to 6 decimal places
        longitude = gps.location.lng(), 6; //get longitude reading with up to 6 decimal places
        hours = gps.time.hour(); //get hour reading
        minutes = gps.time.minute(); //get minute reading
        seconds = gps.time.second(); //get second reading
        
        temperature1 = tcouple1.readTempC(); //get thermocouple 1 reading
        temperature2 = tcouple2.readTempC(); //get thermocouple 2 reading

        //print data to serial monitor
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
        Serial.println(temperature1);
        Serial.print("Thermocouple 2 Temperature: ");
        Serial.println(temperature2);

        Serial.println();
        
        myFile = SD.open(myFileName, FILE_WRITE); //open sd card file in write mode
        myFile.seek(EOF); //find end of file
        
        //print data to sd card file
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
        myFile.println(temperature1);
        myFile.print("Thermocouple 2 Temperature: ");
        myFile.println(temperature2);

        myFile.println();
        
        myFile.close(); //close sd card file

        count = 0; //reset count
      }
    }
  }

  if (count > 5) count = 0; //if count somehow exceeded max, reset it
}
