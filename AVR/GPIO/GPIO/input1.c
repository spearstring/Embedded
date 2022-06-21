/*
 * input1.c
 *
 * Created: 2022-06-17 오후 3:20:21
 *  Author: PKNU
 */ 
#define  F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	
	DDRD = 0x00;	// 포트D 입력으로 설정
	DDRA = 0xFF;	// 포트A 출력으로 설정
	
	while(1)
	{
		if (PIND == 0x01)
		{
			PORTA = 0x01;	// 포트D 입력값이 0x01이면 포트A의 0번비트를 출력
			_delay_ms(300);
			PORTA = 0x00;
		}
		if (PIND == 0x02)
		{
			PORTA = 0x02;
			_delay_ms(300);
			PORTA = 0x00;
		}
		if (PIND == 0x04)
		{
			PORTA = 0x04;
			_delay_ms(300);
			PORTA = 0x00;
		}
		if (PIND == 0x08)
		{
			PORTA = 0x08;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
	}
	
	return 0;
}