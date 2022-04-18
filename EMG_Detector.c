/**
 * @file EMG_Detector.c
 * @author Hung Do
 * @brief EMG Detector measure signal from human muscle and output on LED.
 * @version 0.1
 * @date 2022-04-17
 * 
 * @resource: https://embedds.com/adc-on-atmega328-part-1/
 */
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <IO_Macros.h>
#define USART_BAUDRATE 115200
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define VREF 5
#define POT 10000

//Set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);
//Functions prototype
void USART0Init(void);
int USART0SendByte(char u8Data, FILE *stream);
void InitADC();
uint16_t ReadADC(uint8_t ADCchannel);
void my_delay_ms(unsigned int delay);

int main(void)
{
	// Configure PORT D bit 0 to an output
	DDRD = 0b00000001;

	// Configure PORT C bit 0 to an input
	DDRC = 0b00000000;

	// Configure ADC to be left justified, use AVCC as reference, and select ADC0 as ADC input
	ADMUX = 0b01100000;
	// Enable the ADC and set the prescaler to max value (128)
	ADCSRA = 0b10000111;



	// Main program loop
    while (1) 
    {
		// Start an ADC conversion by setting ADSC bit (bit 6)
		ADCSRA = ADCSRA | (1 << ADSC);
		
		// Wait until the ADSC bit has been cleared
		while(ADCSRA & (1 << ADSC));

		if(ADCH > TRIGPOINT)
		{
			// Turn LED on
			PORTD = PORTD | (1 << PD2);
		}
		else
		{
			// Turn LED off
			PORTD = PORTD & ~(1 << PD2);
		}
	}
}
int implementing(){
	double value, potval;
	InitADC();
	USART0Init();
	DDRD = 0b00000001;
	while(1){
		//reading band gap voltage and recalculating to volts
		value=(double)VREF/1024*ReadADC(14);
		if(value > 100)
		{
			// Turn LED on
			PORTD = PORTD | (1 << PD2);
		}
		else
		{
			// Turn LED off
			PORTD = PORTD & ~(1 << PD2);
		}
		_delay_ms(1000);
	} 
}

//USART initialize
void USART0Init(void) {
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

//USART transmitting data
int USART0SendByte(char u8Data, FILE *stream){
   if(u8Data == '\n')
   {
		USART0SendByte('\r', stream);
   }
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	// Transmit data
	UDR0 = u8Data;
	return 0;
}

void InitADC(){
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC  
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);     
}

uint16_t ReadADC(uint8_t ADCchannel){
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F); 
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}
