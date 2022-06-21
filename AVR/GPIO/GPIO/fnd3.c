/*
 * fnd3.c
 *
 * Created: 2022-06-17 오후 4:50:19
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
		PORTA = 0x3F;
	   
	}
	
	return 0;
}