/*
 * led2.c
 *
 * Created: 2022-06-17 오후 1:55:18
 *  Author: PKNU
 */ 
#define  F_CPU 7432800
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char LED_Data = 0xFF, i;
	DDRA = 0xFF;
	
	while (1)
	{
		LED_Data = 0xFF;
		for (i=0; i < 9; i++)
		{
			PORTA = LED_Data;
			LED_Data <<=1;
			PORTA = 0xFF;
			_delay_ms(1000);
		}
	}
	
	return 0;
}