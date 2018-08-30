/*
 * LCD.h
 *
 * Created: 27.08.2018 21:39:02
 *  Author: mkac
 */ 
#include <avr/io.h>
#include <util/delay.h>


#define LCD_RS_DIR		PORTC_DIR
#define LCD_RS_PORT 	PORTC_DIRSET
#define LCD_RS			PIN0_bm

#define LCD_E_DIR		PORTC_DIR
#define LCD_E_PORT		PORTC_DIRSET
#define LCD_E			PIN1_bm

#define LCD_DB4_DIR		PORTC_DIR
#define LCD_DB4_PORT	PORTC_DIRSET
#define LCD_DB4			PIN2_bm

#define LCD_DB5_DIR		PORTC_DIR
#define LCD_DB5_PORT	PORTC_DIRSET
#define LCD_DB5			PIN3_bm

#define LCD_DB6_DIR		PORTC_DIR
#define LCD_DB6_PORT	PORTC_DIRSET
#define LCD_DB6			PIN4_bm

#define LCD_DB7_DIR		PORTC_DIR
#define LCD_DB7_PORT	PORTC_DIRSET
#define LCD_DB7			PIN5_bm	

//-------------------------------------------------------------------------------------------------
//
// Instrukcje kontrolera Hitachi HD44780
//
//-------------------------------------------------------------------------------------------------

#define HD44780_CLEAR					0x01

#define HD44780_HOME					0x02

#define HD44780_ENTRY_MODE				0x04
#define HD44780_EM_SHIFT_CURSOR		0
#define HD44780_EM_SHIFT_DISPLAY	1
#define HD44780_EM_DECREMENT		0
#define HD44780_EM_INCREMENT		2

#define HD44780_DISPLAY_ONOFF			0x08
#define HD44780_DISPLAY_OFF			0
#define HD44780_DISPLAY_ON			4
#define HD44780_CURSOR_OFF			0
#define HD44780_CURSOR_ON			2
#define HD44780_CURSOR_NOBLINK		0
#define HD44780_CURSOR_BLINK		1

#define HD44780_DISPLAY_CURSOR_SHIFT	0x10
#define HD44780_SHIFT_CURSOR		0
#define HD44780_SHIFT_DISPLAY		8
#define HD44780_SHIFT_LEFT			0
#define HD44780_SHIFT_RIGHT			4

#define HD44780_FUNCTION_SET			0x20
#define HD44780_FONT5x7				0
#define HD44780_FONT5x10			4
#define HD44780_ONE_LINE			0
#define HD44780_TWO_LINE			8
#define HD44780_4_BIT				0
#define HD44780_8_BIT				16

#define HD44780_CGRAM_SET				0x40

#define HD44780_DDRAM_SET				0x80

//-------------------------------------------------------------------------------------------------
//
// Deklaracje funkcji
//
//-------------------------------------------------------------------------------------------------

void LCD_WriteCommand(unsigned char);
void LCD_WriteData(unsigned char);
void LCD_WriteText(char *);
void LCD_GoTo(unsigned char, unsigned char);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Initalize(void);

//-------------------------------------------------------------------------------------------------
//
//
//-------------------------------------------------------------------------------------------------
