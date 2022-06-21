/*
 * lcdTest3.c
 *
 * Created: 2022-06-20 오후 5:11:05
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Lcd.h"

volatile unsigned Time_STOP = 0;

SIGNAL(INT4_vect)
{
	cli();
	if (Time_STOP == 0)
	{
		Time_STOP = 1;
	}
	else
	{
		Time_STOP = 0;
	}
	sei();
}

int main(void)
{
	Byte *str1 = "INTERRUPT!!!";
	
	DDRA = 0xff;
	DDRE = 0x00;
	DDRG = 0x0f;
	EICRA = 1 << ISC41;
	EIMSK = 1 << INT4;
	EIFR = 1 << INT4;
	sei();
	
	Lcd_Init();
	Lcd_Clear();
	
	while (1)
	{
		if (Time_STOP == 0)
		{
			Lcd_Pos(0, 0);
			Lcd_STR(str1);
		}
	}
	
	return 0;
}