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
#include <stdlib.h>

char* data;

int main(void)
{
	data=malloc(sizeof *data *6);
    setUp16MhzExternalOsc();
	UartInit();
	SendData16bittoPcCommon(UsartInitComplited,ClearData);
	SREG|=CPU_I_bm;
	I2cInitMaster();
	SendData16bittoPcCommon(TwiInitComplited,ClearData);
	PORTE_DIRCLR|=PIN0_bm;		//E0 input 
    while (1) 
    {	
		while(PORTE.IN!=PIN0_bm)
		{
			data[0]=0x08;//Ic2ReadSingleAxisABMA220(TwiAddrBMA22,0x04);
			data[1]=0x80;//Ic2ReadSingleAxisABMA220(TwiAddrBMA22,0x08);
			data[2]=0xff;//Ic2ReadSingleAxisABMA220(TwiAddrBMA22,0x12);
			SendData16bittoPcCommon(SendXAxis,data[0]);
			SendData16bittoPcCommon(SendYAxis,data[1]);
			SendData16bittoPcCommon(SendZAxis,data[2]);
			_delay_ms(1000);
		}
		
    }
	free(data);
}

