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
//
//

// This line must always be the first one, before any "include" etc.
#define F_CPU 16000000UL  


#include <avr/io.h>
#include "util/delay.h"
#include "dbg.h"


int main(void)
{


/*
	///////////////////////////////////////////////////////
	// Pure blinking led test
	
	LCD_LED_CONFIG;

    while (1) 
    {
		LCD_LED_SET;
		_delay_ms(2000);
		LCD_LED_RESET;
		_delay_ms(2000);
    }
*/



	//////////////////////////////////////////////////////////
	// UART test for debug purposes.

	// debug 
	LCD_LED_CONFIG;

	const char *msg1 = "The value of val = ";
	const char *msg_crlf= "\r\n";
	uint32_t val = 0;

	DBG_UartInit()	;
	while(1)
	{
		
		//debug
		LCD_LED_SET;
		_delay_ms(1000);
		
		DBG_UartPrintStr(msg1);
		DBG_UartPrintDec(DBG_DecMsgBuff, DBG_DEC_MSG_BUFF_LEN, val);
		DBG_UartPrintStr(msg_crlf);
		
		//debug
		LCD_LED_RESET;
		_delay_ms(1000);
		
		if (val < 99999999) val++;
	}


}

