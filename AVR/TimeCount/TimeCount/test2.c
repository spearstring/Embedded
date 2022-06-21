/*
 * test2.c
 *
 * Created: 2022-06-21 오후 3:58:34
 *  Author: PKNU
 */ 
#include <avr/io.h>				// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>		// AVR 인터럽트에 대한 헤더파일

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0, Shift_Flag = 0;

SIGNAL(TIMER2_OVF_vect);		// Timer2 Overflow0 ISP

SIGNAL(TIMER2_OVF_vect)			// 타이머 오버플로우 인터럽트
{
	cli();						
	TCNT2 = 183;				// 256 - 72 -> 0.01초 마다 한번씩 인터럽트 발생
	timer2Cnt++;				// timer2Cnt 변수를 1 증가

	if (timer2Cnt == 50)		// 0.01s * 50 = 0.5s, 0.5초를 얻기 위한카운트 횟수
	{
		if (Shift_Flag == 0)		// LED0 ~ LED7 이동
		{
			LED_Data <<= 1;			// LED_Data 변수를 좌측으로 쉬프트	
			if (LED_Data == 0x80)	// LED7로 이동하면
			{
				Shift_Flag = 1;		// 우측으로 쉬프트 하도록 설정
			}
		}
		else                        // LED7 ~ LED0 이동
		{
			LED_Data >>= 1;			// LED_Data 변수를 우측으로 쉬프트
			if (LED_Data == 0x01)	// LED0으로 이동하면
			{
				Shift_Flag = 0;		// 좌측으로 쉬프트 하도록 설정
			}
		}
		timer2Cnt = 0;
	}
	sei();
					
}

int main(void)
{
	DDRC = 0xff;		// 포트C 를 출력포트로 설정
	
	TCCR2 = 0x05;		// 프리스케일러 1024로 설정
	
	TCNT0 = 183;		// 256 - 72 -> 0.01초 마다 한번씩 인터럽트 발생
	TIMSK = 0x40;
	TIFR |= 1 << TOV2;
	
	sei();
	
	while (1)
	{
		PORTC = LED_Data;		// 포트C로 변수 LED_Data에 있는 데이터 출력
	}
	return 0;
}