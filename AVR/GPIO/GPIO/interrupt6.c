/*
 * interrupt.c
 *
 * Created: 2022-06-20 오후 12:31:05
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;
volatile unsigned char cnt = 0;

SIGNAL(INT4_vect)
{
	cli();
	Time_STOP = 1;
	cnt = 0;
	sei();
};

SIGNAL(INT6_vect)
{
	cli();
	Time_STOP = 0;
	sei();
};

int main()
{
	unsigned char FND_DATA_TBL [] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
									0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c,
									0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	DDRA = 0xff;
	DDRE = 0x00;
	EICRB = (1 << ISC41) | (1 << ISC61);
	EIMSK = (1 << INT4) | (1 << INT6);
	EIFR = (1 << INT4) | (1 << INT6);
	sei();
	
	while (1)
	{
		PORTA = FND_DATA_TBL[cnt];
		if (Time_STOP == 0)
		{
			cnt++;
			if (cnt > 17)
			{
				cnt=0;
			}
		}
		_delay_ms(200);
	}
	
	return 0;
}