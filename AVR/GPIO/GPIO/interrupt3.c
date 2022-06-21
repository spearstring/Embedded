/*
 * interrupt3.c
 *
 * Created: 2022-06-20 오전 11:22:45
 *  Author: PKNU
 */ 
#define  F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char exchange = 0;

SIGNAL(INT4_vect)
{
	cli();
	if (exchange == 0)
	{
		exchange = 1;
	}
	else
	{
		exchange = 0;
	}
	sei();
}

int main()
{
	unsigned char LED_Data = 0x01;
	DDRE = 0x00;
	DDRA = 0xff;
	EIMSK = 0x10;
	EICRB = 0x03;
	EIFR = 0x10;
	sei();
	
	
	while (1)
	{
		PORTA = LED_Data;
		if (exchange == 0)
		{
			if (LED_Data == 0x80)
			{
				LED_Data = 0x01;
			}
			else LED_Data <<= 1;
		}
		_delay_ms(500);
	}
	
	return 0;
}