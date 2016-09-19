#include "multiplex.h"

#define statusLed 13
#define S0        6
#define S1        5
#define S2        4
#define S3        3
#define enable    2
#define sensPin   A0



static uint16_t  measurement[16];

Multiplex mux1;

void setup() {
  SerialUSB.begin(9600);
  
  while((!SerialUSB)&& (millis()<5000));
  SerialUSB.println("Setting up..");
  mux1.setupMux(S0,S1,S2,S3,enable,sensPin,12);
  digitalWrite(statusLed, HIGH);
  SerialUSB.println("multiplexer enabled");
}

void loop() {

  SerialUSB.println(mux1.createCSV());
  delay(2000);

}

