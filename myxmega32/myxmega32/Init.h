
#include <avr/io.h>
//#include <avr/iox32a4u.h>

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//address sending to pc by usart

#define ClearData	0x00
#define UsartInitComplited	0x00
#define TwiInitComplited	0x01
#define	Err01	0x02
#define Err02	0x03
#define Err03	0x04

#define SendXAxis	0x10
#define SendYAxis	0x11
#define SendZAxis	0x12

#define	SendTmpSens1	0x20
#define	SendTmpSens2	0x21
#define	SendTmpSens3	0x22
#define	SendTmpSens4	0x23

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*initialization files*/

//internal osc

void setUp32MhzInternalOsc();
void clock_init();
void setUp16MhzExternalOsc();

//Usart initial

void UartInit();
void SendChar(char data);
void SendString(char*data);
void SendData8bitToPC(char data);
void SendData16bitToPC(char data[2]);
void SendData8bittoPcCommon(char data);
void SendData16bittoPcCommon(char data,char _data);

//SPI init
void SPIInitMaster();



//I2C init

void I2cInitSlave();
void I2cInitMaster();

#define TwiAddrA8 0x11
#define TwiAddrBMA22 0x0b
void Ic2Write(unsigned char adress,unsigned char data);
void Ic2Read(unsigned char adress);
void Ic2WriteBMA220(unsigned char adress,unsigned char regadress,unsigned char data);
char Ic2ReadSingleAxisABMA220(unsigned char adress,unsigned char regadress);
char* Ic2ReadAllAxisABMA220(unsigned char adress);


//ADC Init

void ADCInit();
void ADCInit8bit();

void ADCOn();
void ADCOff();
uint16_t ADCResult();
uint8_t ADCResult8bit();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


