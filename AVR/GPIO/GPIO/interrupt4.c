/*
 * interrupt4.c
 *
 * Created: 2022-06-20 오전 11:48:42
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag = 1;

SIGNAL(INT5_vect)
{
	cli();
	Shift_flag = 1;
	sei();
}

SIGNAL(INT7_vect)
{
	cli();
	Shift_flag = 2;
	sei();
}

int main()
{
	unsigned char LED_Data = 0x01;
	DDRE = 0x00;
	DDRA = 0xff;
	EICRB = (1 << ISC51) | (1 << ISC71);
	EIMSK = (1 << INT5) | (1 << INT7);
	EIFR = (1 << INT5) | (1 << INT7);
	sei();

	while (1)
	{
		PORTA = LED_Data;
		if (Shift_flag == 1)
		{
			if (LED_Data == 0x80)
			{
				LED_Data = 0x01;
			}
			else
			{
				LED_Data <<= 1;
			}
		}
		else if (Shift_flag == 2)
		{
			if (LED_Data == 0x01)
			{
				LED_Data = 0x80;
			}
			else
			{
				LED_Data >>= 1;
			}
		}
		_delay_ms(300);
	}

	return 0;
}