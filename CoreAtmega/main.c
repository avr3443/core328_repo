/*
 * CoreAtmega.c
 *
 * Created: 13.07.2019 21:20:10
 * Author : arek1
 */ 


// pc virtual com and usart test
// xplained devboard -> 16 MHz
//
// Use #define F_CPU 16000000UL as the first line of the code.
// Or -DF_CPU=16000000UL in C compiler symbol settings.
//


//TODO:
//


#define F_CPU 16000000UL  


#include <avr/io.h>
#include "util/delay.h"


// Blinking LED for tests.
#define LCD_LED_CONFIG	DDRB |=  (1 << PB5)
#define LCD_LED_SET		PORTB |= (1 << PB5)
#define LCD_LED_RESET	PORTB &= ~(1 << PB5)


#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU/(USART_BAUDRATE*16UL)))-1)



void serial_init() 
{
	
	//power_usart0_enable();
	
	/*
	// initialize USART (must call this before using it)
	//UBRR0=UBRR_VALUE; // set baud rate
	UBRR0=51;
	UCSR0A=0x00;
	UCSR0B|=(1<<TXEN0); //enable transmission only
	UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00); // no parity, 1 stop bit, 8-bit data
	*/
	
	
	
	// configure ports double mode
	//UCSR0A = _BV(U2X0);
	UCSR0A = 0x00;

	// configure the ports speed 9600
	UBRR0H = 0x00;
	//UBRR0L = 51;  // it makes 19200, like for 16 MHz clock ?
	UBRR0L = 103;  // it makes 9600, for 16 MHz clock

	// asynchronous, 8N1 mode
	UCSR0C |= 0x06;
	
	// rx/tx enable
	//UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
		
}


void serial_send(unsigned char data)
{

	// send a single character via USART
	while ( !(UCSR0A & ( 1<<UDRE0 )) ) {}; //wait while previous byte is completed
	UDR0 = data; // Transmit data

}


void serial_break()
{

	serial_send(10); // new line
	serial_send(13); // carriage return

}


void serial_comma()
{

	serial_send(','); // comma
	serial_send(' '); // space

}


void serial_number(long val)
{
	// send a number as ASCII text
	char preVal=' ';
	long divby=100000000; // change by dataType

	while( divby >= 1 )
	{
		serial_send('0' + val / divby);
		val -= (val / divby) * divby;
		divby /= 10;
	}
	
}


int main(void)
{

	// debug 
	LCD_LED_CONFIG;


	serial_init();
	int i;
	for (;;) {
		
		//debug
		LCD_LED_SET;
		
		//for(i='A';i<='Z';i++){serial_send(i);} // send the alphabet
		//serial_break();
		//
		//serial_number(10140000+123); // send a big number
		//serial_break();
		
		serial_send(0x62);  //B 0x42, b 0x62
		
		_delay_ms(1000); // wait a while		
		
		//debug		
		LCD_LED_RESET;
		_delay_ms(1000);
		
	}



/*
	LCD_LED_CONFIG;

    while (1) 
    {
		LCD_LED_SET;
		_delay_ms(2000);
		LCD_LED_RESET;
		_delay_ms(2000);
    }
*/

}

