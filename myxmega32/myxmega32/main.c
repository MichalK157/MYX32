/*
 * myxmega32.c
 *
 * Created: 22.08.2018 15:15:47
 * Author : mkac
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "LCD.h"
#include <stdbool.h>
#include "Init.h"

int main(void)
{
    setUp16MhzExternalOsc();
	
	UartInit();
	
	PORTE_DIRCLR|=PIN0_bm|PIN1_bm|PIN2_bm|PIN3_bm;
	bool state=false;
	uint8_t value=0;
	
    while (1) 
    {	
		if(PORTE.IN==0x00)
			state=true;
		
		
		while(state){
			while(!(USARTD0_STATUS&USART_DREIF_bm));
			USARTD0_DATA=value;
			while(!(USARTD0_STATUS&USART_DREIF_bm));
			USARTD0_DATA=0x09;
			_delay_ms(30);
			state=false;
			}
		
    }
}

