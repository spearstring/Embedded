/*
 * test2.c
 *
 * Created: 2022-06-22 오전 11:39:11
 *  Author: PKNU
 */ 
#include <avr/io.h>					// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>			// AVR 인터럽트에 대한 헤더파일

volatile unsigned char LED_Date = 0x00;

SIGNAL(TIMER3_OVF_vect)
{
	cli();
	
	// 65536 - 7200 = 58336-> 1초 마다 한번씩 인터럽트 발생
	TCNT3 = 58336;
	LED_Date++;					// LED_Data 변수1 증가
	
	if (LED_Date > 0xFF)
	{
		LED_Date = 0;
	}
	
	sei();
}

int main(void)
{
	DDRC = 0xff;				// 포트C 를 출력포트로 설정
	
	TCCR3A = 1 << COM3C0;	
	TCCR3B = (1 << CS32) | (1 << CS30);		// 프리스케일러 1024;
	
	// 65536 - 7200 = 58336-> 1초 마다 한번씩 인터럽트 발생
	TCNT3 = 58336;
	ETIMSK = 1 << TOIE3;
	ETIFR |=1 << TOV3;
	
	sei();
	
	while (1)
	{
		PORTC = LED_Date;		//포트C로 변수 LED_Data에 있는 데이터 출력
	}
	return 0;
}