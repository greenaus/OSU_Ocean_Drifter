# OSU_Ocean_Drifter
The code repo for the HC 407 ocean drifter dev-kit


## ArudinoGPS.ino Dependencies:

Adafruit Circuit Playground
Adafruit MAX31856 Library

DHT sensor library

Tiny GPS

## Current Arduino Pinout
### DHT Humidity Sensor:
plus  -> 5V

out   -> D2

minus -> GND

### GPS
VCC -> 5V  (Needs external source. Arudino can't provide enough power to run!)

RX  -> D3

TX  -> D4

GND -> GND


### Max31856 Thermocouple:
Vin -> 5V

GND -> GND

SCK -> D13

SDO -> D12

SDI -> D11

CS  -> D10



### SD Card (Tentative):
CS   -> D9

SCK  -> D13

MOSI -> D11

MISO -> D12

VCC  -> 5V

GND  -> GND

