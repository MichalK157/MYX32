#include "Init.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

volatile unsigned char noofbytes;
volatile unsigned char databuff[3];
volatile unsigned char databuffread[6];
volatile unsigned char datacount;
volatile unsigned char transfercomplited;



void setUp32MhzInternalOsc()
{
	OSC_CTRL |= OSC_RC32MEN_bm; //Setup 32Mhz crystal
	
	while(!(OSC_STATUS & OSC_RC32MRDY_bm));
	
	CCP = CCP_IOREG_gc; //Trigger protection mechanism
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc; //Enable internal  32Mhz crystal
	
}
void clock_init()
{
	OSC_PLLCTRL=OSC_PLLFAC3_bm; //select internal 2MHz oscillator as PLL clock source, PLL multiplication factor as 8
	
	OSC_CTRL=OSC_PLLEN_bm; //enable PLL
	
	while(!(OSC_STATUS & OSC_PLLRDY_bm)); //wait until PLL is locked to desired frequency and ready to use
	
	CCP=0xd8; //write Configuration Change Protection register
	
	CLK_CTRL=CLK_SCLKSEL2_bm; //select PLL as system clock source
	
	CCP=0xd8; //write Configuration Change Protection register
	
	CLK_PSCTRL=CLK_PSADIV0_bm; //select Prescaler A as 2, Prescaler B and Prescaler C as 1, Clksys=16MHz, Clkper4=Clkper2=Clkper=Clkcpu=8MHz
	
	CLK_RTCCTRL=CLK_RTCEN_bm; //enable RTC clock source as 1KHz from 32KHz ULP internal oscillator
}
void setUp16MhzExternalOsc()
{
	//PORTD_DIR = 0x01;
	//16MHz external crystal
	OSC_XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_16KCLK_gc;
	//Enable external oscillator
	OSC_CTRL |= OSC_XOSCEN_bm;
	//Wait for clock stabilization
	while(!(OSC_STATUS & OSC_XOSCRDY_bm));
	// Selects clock system as external clock
	// through change protection mechanism
	CCP = CCP_IOREG_gc;
	CLK_CTRL = CLK_SCLKSEL_XOSC_gc;
}

void UartInit()
{
	PORTD_DIRSET=0x08;
	PORTD_OUTSET=0x08;
	USARTD0_CTRLB=0x18;
	USARTD0_CTRLC=0x03;
	USARTD0_BAUDCTRLA=0x19;
	USARTD0_BAUDCTRLB=0x20;
	
}

void SendChar(char data)
{
	while(!(USARTD0_STATUS&USART_DREIF_bm));
	USARTD0_DATA=data;
}

void SendString(char*data)
{
	while (*data)
	{
		SendChar(*data++);
	}
	
}

void SendData8bitToPC(char data)
{
	SendChar(data);
	SendChar(0x09);
}

void SendData16bitToPC(char data[2])
{
	SendChar(data[0]);
	SendChar(data[1]);
	SendChar(0x09);
}

void SPIInitMaster()
{
	
}

void I2cInitSlave()
{
	
}

void I2cInitMaster()
{
	TWIC_MASTER_BAUD=0x4b;
	TWIC_CTRL=0x00;
	TWIC_MASTER_CTRLA|=	TWI_MASTER_INTLVL_gm|TWI_MASTER_RIEN_bm|TWI_MASTER_WIEN_bm|TWI_MASTER_ENABLE_bm;
	TWIC_MASTER_CTRLB=0x00;
	TWIC_MASTER_CTRLC=0x00;
	TWIC_MASTER_STATUS|=TWI_MASTER_RIF_bm|TWI_MASTER_WIF_bm|TWI_MASTER_ARBLOST_bm|TWI_MASTER_BUSERR_bm|TWI_MASTER_BUSSTATE0_bm;
}

void Ic2Write(unsigned char adress,unsigned char data)
{
	noofbytes=1;
	datacount=0;
	transfercomplited=0;
	databuff[0]=adress;
	databuff[1]=data;
	TWIC_MASTER_ADDR=0xd0;
	while(transfercomplited!=1);
}


void Ic2Read(unsigned char adress)
{
	noofbytes=0;
	datacount=0;
	transfercomplited=0;
	databuff[0]=adress;
	TWIC_MASTER_ADDR=0xd0;
	while(transfercomplited!=1);
	noofbytes=6;
	datacount=0;
	transfercomplited=0;
	TWIC_MASTER_ADDR=0xd1;
	while(transfercomplited!=1);
}

void Ic2WriteBMA220(unsigned char adress,unsigned char regadress,unsigned char data)
{
	noofbytes=2;
	datacount=0;
	transfercomplited=0;
	databuff[0]=adress;
	databuff[1]=regadress;
	databuff[2]=data;
	TWIC_MASTER_ADDR=0xd0;
	while(transfercomplited!=1);
}

void Ic2ReadSingleAxisABMA220(unsigned char adress,unsigned char regadress)
{
	noofbytes=1;
	datacount=0;
	transfercomplited=0;
	databuff[0]=adress;
	databuff[1]=regadress;
	TWIC_MASTER_ADDR=0xd0;
	while(transfercomplited!=1);
	noofbytes=1;
	datacount=0;
	transfercomplited=0;
	TWIC_MASTER_ADDR=0xd1;
	while(transfercomplited!=1);
}


void Ic2ReadAllAxisABMA220(unsigned char adress)
{
	noofbytes=1;
	datacount=0;
	transfercomplited=0;
	databuff[0]=adress;
	databuff[1]=0x04;
	TWIC_MASTER_ADDR=0xd0;
	while(transfercomplited!=1);
	//////////////////////////////////////////////////////////////////////////
	//repeat start and slave adddress 
	//////////////////////////////////////////////////////////////////////////
	noofbytes=6;
	datacount=0;
	transfercomplited=0;
	TWIC_MASTER_ADDR=0xd1;
	while(transfercomplited!=1);
}

void ADCInit()
{
	ADCA_CTRLB|=ADC_CURRLIMIT1_bm|ADC_CONMODE_bm;
	ADCA_REFCTRL|=ADC_REFSEL0_bm;
	ADCA_EVCTRL=0x00;
	ADCA_PRESCALER|=ADC_PRESCALER2_bm;
	ADCA_INTFLAGS|=ADC_CH_INPUTMODE0_bm;
	ADCA_CH0_CTRL|=ADC_CH_INPUTMODE0_bm;
	ADCA_CH0_MUXCTRL|=ADC_CH_MUXPOS0_bm;
	ADCA_CTRLA|=ADC_ENABLE_bm;
}

void ADCInit8bit()
{
	
	ADCA_CTRLB|=ADC_CURRLIMIT1_bm|ADC_CONMODE_bm|ADC_RESOLUTION_8BIT_gc;
	ADCA_REFCTRL|=ADC_REFSEL2_bm;
	ADCA_EVCTRL=0x00;
	ADCA_PRESCALER|=ADC_PRESCALER2_bm;
	ADCA_INTFLAGS|=ADC_CH_INPUTMODE0_bm;
	ADCA_CH0_CTRL|=ADC_CH_INPUTMODE0_bm;
	ADCA_CH0_MUXCTRL|=ADC_CH_MUXPOS0_bm;
	ADCA_CTRLA|=ADC_ENABLE_bm;
	/*
	ADCA.CTRLA=ADC_ENABLE_bm;
	ADCA.CTRLB=0x06;
	ADCA.CH0.CTRL=0x01;
	ADCA.CH0.MUXCTRL=0x08;
	ADCA.PRESCALER=ADC_PRESCALER2_bm;
	PORTD_DIRCLR=0x02;
	ADCA.CH0.CTRL=ADC_CH_INPUTMODE0_bm;
	ADCA.REFCTRL=ADC_REFSEL0_bm;
	*/
	
	
}

void ADCOn()
{
	ADCA.CTRLA |=0x80;
}

void ADCOff()
{
	ADCA.CTRLA &=~0x80;
}

uint16_t ADCResult()
{
	ADCA_CTRLA|=ADC_CH0START_bm;
	while(!(ADCA_INTFLAGS&ADC_CH0IF_bm));
	ADCA_INTFLAGS=ADC_CH0IF_bm;
	return ADCA_CH0_RES;
}

uint8_t ADCResult8bit()
{
ADCA_CTRLA|=ADC_CH0START_bm;
while(!(ADCA_INTFLAGS&ADC_CH0IF_bm));
ADCA_INTFLAGS=ADC_CH0IF_bm;
return ADCA_CH0_RES;
}


//////////////////////////////////////////////////////////////////////////
//ISR
//////////////////////////////////////////////////////////////////////////

ISR(TWIC_TWIM_vect)
{
	//twi atri is lost send stop
	if (TWIC_MASTER_STATUS&(1<<TWI_MASTER_ARBLOST_bp))
	{
		TWIC_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
	}
	
	//twi error flag or nack then stop
	
	if((TWIC_MASTER_STATUS&(1<<TWI_MASTER_BUSERR_bp))||(TWIC_MASTER_STATUS &(1<<TWI_MASTER_RXACK_bp)))
	{
		TWIC_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
	}
	
	//TWI WRITE FLAG
	
	if(TWIC_MASTER_STATUS&(1<<TWI_MASTER_WIF_bp))
	{
		if(!(TWIC_MASTER_STATUS&(1<<TWI_MASTER_RXACK_bp)))
		{
			
			TWIC_MASTER_DATA=databuff[datacount++];			//write data
			
			if(noofbytes){
				noofbytes--;
			}
			else
			{
				
				TWIC_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
				transfercomplited=1;
			}
		}
	}
	
	//twi read falg
	
	if(TWIC_MASTER_STATUS&(1<<TWI_MASTER_RIF_bp))
	{
		databuffread[datacount++]=TWIC_MASTER_DATA;
		
		if(noofbytes==0)
		{
			TWIC_MASTER_CTRLC=(1<<TWI_MASTER_ACKACT_bp)|(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
			transfercomplited=1;
		}
		else
		{
			noofbytes--;
			TWIC_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
		}
	}
	
}