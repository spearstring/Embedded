/*
 * fnd2.c
 *
 * Created: 2022-06-17 오후 4:30:05
 *  Author: PKNU
 */
#define F_CPU 7432800UL 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	
	DDRA = 0xFF;
	DDRD = 0x00;
	
	while (1)
	{
	
		if (PIND == 0x01)
		{
			PORTA = 0x3F;	
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x02)
		{
			PORTA = 0x06;
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x04)
		{
			PORTA = 0X5B;
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x08)
		{
			PORTA = 0X4F;
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x10)
		{
			PORTA = 0X66;
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x20)
		{
			PORTA = 0X6D;
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x40)
		{
			PORTA = 0X7D;
			_delay_ms(500);
			PORTA = 0x00;
		}
		if (PIND == 0x80)
		{
			PORTA = 0X27;
			_delay_ms(500);
			PORTA = 0x00;
		}
		
	}
	
	return 0;
}