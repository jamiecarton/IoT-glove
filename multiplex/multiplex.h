#ifndef multiplex_h
#define multiplex_h


#include "Arduino.h"

#define start	0xFF

class Multiplex {
	
	public:
		
		Multiplex();
		void setupMux(uint8_t add0, uint8_t add1, uint8_t add2, uint8_t add3, uint8_t enablePin, uint8_t analogPin, uint8_t resolution);
		uint16_t readFromMux(uint8_t channel);
		uint16_t readAllChannels(uint16_t data[]);
		String createCSV();
	
	private:
		
		uint8_t S0;
		uint8_t S1;
		uint8_t S2;
		uint8_t S3;
		uint8_t enable;
		uint8_t adc;
		uint8_t state;
		
		float factor;
		
		void setChannel(uint8_t channel);
		
	
};


#endif
 