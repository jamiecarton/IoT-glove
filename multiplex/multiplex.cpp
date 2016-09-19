/*
 *	Multiplex library
 */

#include "Arduino.h"
#include "multiplex.h"



 Multiplex::Multiplex()
 {
		 
 }
 
 /*
	setupMux function requires four adress pins
	One enable pin and analog pin on the device
	The resolution is optional default is 12 bits
 */
 
void Multiplex::setupMux(uint8_t add0, uint8_t add1, uint8_t add2, uint8_t add3, uint8_t enablePin, uint8_t analogPin, uint8_t resolution = 12)
{	
	
	uint8_t state = start;
	 pinMode(add0, OUTPUT);
	 pinMode(add1, OUTPUT);
	 pinMode(add2, OUTPUT);
	 pinMode(add3, OUTPUT);
	 pinMode(enablePin, OUTPUT);
	 
	  S0 = add0;
	  S1 = add1;
	  S2 = add2;
	  S3 = add3;
	  enable = enablePin;
	  adc = analogPin;
	  analogReadResolution(resolution);
	
	 
	 if (resolution==12){float factor = 0.806;}
	 else if (resolution == 10){ float factor = 3.23;}
	 else{ 
			if (!SerialUSB)
				{
				analogReadResolution(12);
				float factor = 0.806;
			}
				else{
					SerialUSB.println("No valid resolution selected use 12 or 10 bits ");
				}
		}
	digitalWrite(enable, HIGH);
}

/*
	readFromMux function is to read from a specific fuction
	And uses the private fuction setChannel to choose the channel
*/

uint16_t Multiplex::readFromMux(uint8_t channel)
{
  uint16_t data=0;
  setChannel(channel);
  delay(1);
  data = analogRead(adc);
  digitalWrite(enable, HIGH);
  return data;
}

/*
	Private fuction to set the channel
*/

void Multiplex::setChannel(uint8_t channel)
{
		
		state = channel;
	digitalWrite(enable,LOW);
  
  switch (state){

      case start:
		state = channel;
      break;

      case 0:       //0000
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      break;

      case 1:       //1000
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      break;

      case 2:       //0100
      digitalWrite(S0,LOW);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      break;

      case 3:       //1100
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      break;

      case 4:       //0010
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
      break;

      case 5:       //1010
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
      break;

      case 6:       //0110
      digitalWrite(S0,LOW);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
      break;

      case 7:       //1110
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
      break;

      case 8:       //0001
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
    //  SerialUSB.println("channel 8");
      break;

      case 9:       //1001
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
     // SerialUSB.println("channel 9");
      break;

      case 10:       //0101
      digitalWrite(S0,LOW);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      //SerialUSB.println("channel 10");
      break;

      case 11:       //1101
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
     // SerialUSB.println("channel 11");
      break;

      case 12:       //0011
      digitalWrite(S0,LOW);
      digitalWrite(S1,LOW);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      break;

      case 13:       //1011
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      break;

      case 14:       //0111
      digitalWrite(S0,LOW);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      break;

      case 15:       //1111
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      break;

      default:
      break;
      
  }
}

/*
	readAllChannels single function to read all 16 channels
	Uses a static uint16_t array of 16 as argument to collect the measurements
	
*/

uint16_t Multiplex::readAllChannels(uint16_t data[16])
{
	
	for (int i=0; i<16; i++){
		data[i]=readFromMux(i);
	}
	return *data;
}

/*
	creates a CSV string of all 16 channels
*/

String Multiplex::createCSV()
{
	String data = "All 16 channel: ";
	data += String(readFromMux(0)) + ",";
	data += String(readFromMux(1)) + ",";
	data += String(readFromMux(2)) + ",";
	data += String(readFromMux(3)) + ",";
	data += String(readFromMux(4)) + ",";
	data += String(readFromMux(5)) + ",";
	data += String(readFromMux(6)) + ",";
	data += String(readFromMux(7)) + ",";
	data += String(readFromMux(8)) + ",";
	data += String(readFromMux(9)) + ",";
	data += String(readFromMux(10)) + ",";
	data += String(readFromMux(11)) + ",";
	data += String(readFromMux(12)) + ",";
	data += String(readFromMux(13)) + ",";
	data += String(readFromMux(14)) + ",";
	data += String(readFromMux(15));
	
	return data;
}

