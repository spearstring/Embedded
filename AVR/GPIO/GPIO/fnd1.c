/*
 * fnd1.c
 *
 * Created: 2022-06-17 오후 4:21:38
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;
	
	while (1)
	{
		PORTA = 0x03f;	//0b 0011 1111
		_delay_ms(1000);
		PORTA = 0x06;
		_delay_ms(1000);
		
	}
	return 0;
}