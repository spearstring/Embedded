/*
 * test3.c
 *
 * Created: 2022-06-21 오후 4:18:50
 *  Author: PKNU
 */ 
#include <avr/io.h>				// AVR 입출력에  대한 헤더 파일
#include <avr/interrupt.h>		// AVR 인터럽트에 대한 헤더 파일

// 7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c,
								0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e,
								0x79, 0x71, 0x08, 0x80};
								
volatile unsigned char time_s = 0;		// 초를 세는 변수
unsigned char timer0cnt = 0;

SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += 72;				// 0.01초 후에 인터럽트 발생
	timer0cnt++;			// timer0Cnt 변수 1 증가
	
	// 0.01s * 100 = 1s		// 1초를 얻기 위한 카운트 횟수
	if (timer0cnt == 100)
	{
		if (time_s >= 16)	// time_s 변수는 16까지만 증가
		{
			time_s = 0;     // 16되면 0으로 초기화
		}
		else           
		{
			time_s++;
		}
		
		timer0cnt = 0;
	}
	
	sei();
}

int main(void)
{
	DDRA = 0xff;			// 포트A를 출력포트로 설정
	
	TCCR0 = 0x07;			// 프리스케일러 1024
	OCR0 = 72;				// 0.01초 마다 한번씩 인터럽트 발생
	TIMSK = 0x02;			// 출력비교 인터럽트 활성화
	TIFR |=1 << OCF0;
	
	sei();
	
	while (1)
	{
		PORTA = FND_DATA_TBL[time_s];		// 포트A에 FND Table 값을 출력
	}
	
	return 0;
}