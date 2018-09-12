/*
 * myxmega32.c
 *
 * Created: 22.08.2018 15:15:47
 * Author : mkac
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "Init.h"


int main(void)
{
    setUp16MhzExternalOsc();
	UartInit();
	SendData8bitToPC(UsartInitComplited);
	
	SREG|=CPU_I_bm;
	I2cInitMaster();
	//PORTE_DIRCLR|=PIN0_bm|PIN1_bm|PIN2_bm|PIN3_bm;
	bool state=false;
	uint8_t value=0;
	
    while (1) 
    {	
		
		
    }
}

