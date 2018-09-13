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

char* data;

int main(void)
{
    setUp16MhzExternalOsc();
	UartInit();
	SendData16bittoPcCommon(UsartInitComplited,ClearData);
	SREG|=CPU_I_bm;
	I2cInitMaster();
	SendData16bittoPcCommon(TwiInitComplited,ClearData);
    while (1) 
    {	
		data=Ic2ReadAllAxisABMA220(TwiAddrBMA22);
		SendData16bittoPcCommon(SendXAxis,data[0]);
		SendData16bittoPcCommon(SendYAxis,data[1]);
		SendData16bittoPcCommon(SendZAxis,data[2]);
		_delay_ms(1000);
    }
}

