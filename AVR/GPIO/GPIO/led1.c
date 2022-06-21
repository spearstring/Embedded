/*
 * led1.c
 *
 * Created: 2022-06-17 오전 11:45:59
 *  Author: PKNU
 */ 
#define F_CPU 7372800
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;	// portA를 출력으로 설정 0b1111 1111 123456789ABCDEF

	
	while (1)
	{
		PORTA = 0xFF;	// PROTA 모두 1로 출력	
		_delay_ms(1000);	// 1000ms 시간 지연
		PORTA = 0x00;	// PROTA 모두 0으로 출력
		_delay_ms(1000);	// 1000ms 시간 지연

	}
	
	return 0;
}