#include <avr/io.h>
#include <util/delay.h>
#include "IO_Macros.h"

#define A  PC0

uint16_t ReadADC();
void ADC_init();
void my_delay_ms(unsigned int delay);

int main(void) {
	uint8_t addramask = ~(1 << A);
	ADC_init();
	
	while (1) {
		uint16_t wave_val = ReadADC() / 2;	// currently configured for 0 - 1696
		
		//Do something with the detector and another sensor

		PORTB |= (1 << A);
		
	}
}

void ADC_init () {
	ADCSRA = (1 << ADEN);    				// enable ADC
	ADCSRA |= (1 << ADATE) | (1 << ADSC);   // start conversation
	ADMUX = (1 << REFS0);
}

uint16_t ReadADC() {
	uint8_t LS_data = ADCL; 
	uint8_t MS_data = ADCH;
	uint16_t adc_data = (MS_data << 8) | LS_data;
	return adc_data;
}
/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(unsigned int delay) {
	unsigned int i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	for (i=0; i < delay % 10; i++)
	{
		_delay_ms(1);
	}
}