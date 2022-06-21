/*
 * TimeCount.c
 *
 * Created: 2022-06-21 오후 3:31:19
 * Author : PKNU
 */ 
#include <avr/io.h>				// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>		// AVR 인터럽트에 대한 헤더파일

volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;
SIGNAL(TIMER0_OVF_vect);		// Timer0 Overflow0 ISP

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 183;				// 256 - 72 = 183 -> 0.01초 마다 한번씩 인터럽트 발생
	timer0Cnt++;				// timer0Cnt 변수를 1 증가
	if (timer0Cnt == 100)		// 0.01s * 100 = 1s를 얻기 위한 카운트 횟수
	{
		LED_Data++;				// LED_Data 변수를 1증가
		if (LED_Data > 0x0f)
		{
			LED_Data = 0;
		}
		
		timer0Cnt = 0;
	}
	sei();
}

int main(void)
{
    DDRC = 0x0f;
	TCCR0 = 0x07;
	TCNT0 = 183;
	TIMSK = 0x01;
	TIFR |=1 << TOV0;
	sei();
	
    while (1) 
    {
		PORTC = LED_Data;		// 포트C로 변수 LED_Data에 있는 데이터 출력
    }
}

