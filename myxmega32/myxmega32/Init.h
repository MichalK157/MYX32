
#include <avr/io.h>
//#include <avr/iox32a4u.h>


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


//SPI init
void SPIInitMaster();


//I2C init

void I2cInit();

//ADC Init

void ADCInit();
void ADCInit8bit();

void ADCOn();
void ADCOff();
uint16_t ADCResult();
uint8_t ADCResult8bit();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////