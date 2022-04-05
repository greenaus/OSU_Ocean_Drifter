#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
#include <Adafruit_MAX31856.h>
#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 2     // Digital pin connected to the DHT sensor

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
int option =2;

SoftwareSerial gpsSerial(3,4);//rx,tx 
TinyGPS gps; // create gps object 
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10, 11, 12, 13);
DHT dht(DHTPIN, DHTTYPE);

void setup(){ 
  Serial.begin(9600); // connect serial 
  //Serial.println("The GPS Received Signal:"); 
  gpsSerial.begin(9600); // connect gps sensor 

  maxthermo.begin();
  dht.begin();
  
  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
  
} 

void loop(){ 
  
  if(option == 1 ){
 
  
    while(gpsSerial.available()){ // check for gps data 
      if(gps.encode(gpsSerial.read()))// encode gps data 
      {  
        gps.f_get_position(&lat,&lon); // get latitude and longitude 
    // display position 
    
        Serial.print("Position: "); 
        Serial.print("Latitude:"); 
        Serial.print(lat,6); 
        Serial.print(";"); 
        Serial.print("Longitude:"); 
        Serial.println(lon,6);  
       
        Serial.print(lat); 
        Serial.print(" "); 
      } 
    } 
    String latitude = String(lat,6); 
    String longitude = String(lon,6); 
    Serial.println(latitude+";"+longitude); 
  }

  else if (option == 2){
    Serial.print("Cold Junction Temp: ");
    Serial.println(maxthermo.readCJTemperature());
  
    Serial.print("Thermocouple Temp: ");
    Serial.println(maxthermo.readThermocoupleTemperature());
    
  
  }
  

  else if (option == 3){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
  
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.println(F("°F"));
  }
  else{
    Serial.println("No Sensor Selected!");  
  }
  
  delay(5000); 
} 
