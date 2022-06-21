/*
 * LCD.c
 *
 * Created: 2022-06-20 오후 2:53:58
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"


int main(void)
{
	Byte *str1 = "LCD TEST";
	Byte *str2 = "ATmage 128";
	
    DDRA = 0x0f;
	
	LcdInit_4bit();
	Lcd_Clear();
	
    while (1) 
    {
		Lcd_Pos(0, 0);
		Lcd_STR(str1);
		Lcd_Pos(1, 0);
		Lcd_STR(str2);
    }
	
	return 0;
}

