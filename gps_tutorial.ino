#include <TinyGPS++.h>

int count = 0;

double _latitude = 0;
double _longitude = 0;
double _hour = 0;
double _minute = 0;
double _second = 0;
float _temp_celsius = 0;

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

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
  //Serial.println(count);
  if (count == 5) {
    while (Serial1.available()) { //if gps is reading
      gps.encode(Serial1.read()); //read from gps
      if (gps.location.isUpdated()) { //if successful reading
        //save gps data
        _latitude = gps.location.lat(), 6;
        _longitude = gps.location.lng(), 6;
        _hour = gps.time.hour();
        _minute = gps.time.minute();
        _second = gps.time.second();
        
        //print gps data
        Serial.print("Latitude: "); 
        Serial.print(_latitude);
        Serial.print(", Longitude: "); 
        Serial.println(_longitude);
        Serial.print("Hour: ");
        Serial.print(_hour);
        Serial.print(", Minute: ");
        Serial.print(_minute);
        Serial.print(", Second: ");
        Serial.println(_second);

        count = 0;
      }
    }
  }
  if (count > 5) count = 0;
}
