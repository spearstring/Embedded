/*
 * TimeCount16.c
 *
 * Created: 2022-06-22 오전 10:15:28
 * Author : PKNU
 */ 

#include <avr/io.h>					// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>			// AVR 인터럽트에 대한 헤더 파일

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt = 0;

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	
	timer1Cnt++;					// timer0Cnt 변수 1 증가
	
	if (timer1Cnt == 225)			// 1/255s * 255 = 1s, 1초를 얻기 위한 카운트 횟수
	{
		LED_Data++;
		
		if (LED_Data > 0xff)
		{
			LED_Data = 0;
		}
		
		timer1Cnt = 0;
	}
	sei();
}

int main(void)
{
    DDRC = 0xff;					// 포트C를 출력포트로 설정
	
	TCCR1A = 1 << WGM10;					
	TCCR1B = 1 << CS12; 					// 프리스케일러 1
	
	TCNT1 = 0;						// 0 -> 1/225초 마다 한번씩 인터럽트 발생
	TIMSK = 1 << OCIE1B;
	TIFR |=1 << TOV1;
	
	sei();
	
    while (1) 
    {
		PORTC = LED_Data;
    }
	
	return 0;
}

