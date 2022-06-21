/*
 * interrupt2.c
 *
 * Created: 2022-06-20 오전 10:39:32
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char exchange = 0;

SIGNAL (INT4_vect)
{
	exchange = ~exchange;
}

int main()
{
	DDRE = 0x00;
	DDRA = 0xFF;
	EIMSK = 1 << INT4;
	EICRB = 1 << ISC41;
	sei();
	
	
	while (1)
	{
		if (exchange)
		{
			PORTA = 0xff;
		}
		else
		{
			PORTA = 0x00;
		}
	}
	
	return 0;
}