//libraries/files included
#include <MAX6675.h>

//pin assignments
#define CS_PIN1 13
#define CS_PIN2 12

//thermocouple initialization
MAX6675 tcouple1(CS_PIN1);
MAX6675 tcouple2(CS_PIN2);

//data variables
int count = 0;
double temperature1 = 0;
double temperature2 = 0;

void setup() {
  
  //initialize serial
  Serial.begin(9600); 
  
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
  count++; //increment count each second 
}

void loop() {

//run the part every 5 second.
if (count == 5) {
  
        //get thermocouples reading
        temperature1 = tcouple1.readTempC();
        temperature2 = tcouple2.readTempC();
        
        //print data to serial monitor
        Serial.print("Thermocouple 1 Temperature: ");
        Serial.println(temperature1);
        Serial.print("Thermocouple 2 Temperature: ");
        Serial.println(temperature2);
        Serial.println();
        
        count = 0; //reset count
      }
  if (count > 5) count = 0; //if count somehow exceeded max, reset it
}
