/*
 * test4.c
 *
 * Created: 2022-06-21 오후 4:57:27
 *  Author: PKNU
 */ 
#include <avr/io.h>				// AVR 입출력에  대한 헤더 파일
#include <avr/interrupt.h>		// AVR 인터럽트에 대한 헤더 파일

// 7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c,
								0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e,
								0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s = 0;		// 0.5초를 세는 변수
volatile unsigned char Time_STOP = 0;	// 숫자 증가 및 정지시키는 변수

unsigned char timer0cnt = 0;

SIGNAL(TIMER2_COMP_vect)
{
	cli();						// 전체 인터럽트를 금지
	OCR2 += 72;					// 0.01초 후에 인터럽트 발생
	timer0cnt++;				// timer0Cnt 변수를 1 증가
	if (timer0cnt == 50)		// 0.01s * 50 = 0.5s, 0.5초를 얻기 위한 카운트 횟수
	{
		if (Time_STOP ==0)		// Time_STOP이 0인 경우에만
		{
			if (time_s >= 16)
			{
				time_s = 0;		// time_s 변수는 16까지만 증가
			}
			else
			{
				time_s++;		// 16되면 0으로 초기화
			}
		}
		timer0cnt=0;
	}
	sei();						// 전체 인터럽트를 허용
}

SIGNAL(INT4_vect)				// 인터럽트 서비스 루틴
{
	cli();						// 전체 인터럽트 금지
	
	if (Time_STOP == 0)			// Time_STOP이 0인 경우에만
	{
		Time_STOP = 1;			// Time_STOP에 1을 입력
	}
	else                        // Time_STOP이 1인 경우에만
	{
		Time_STOP = 0;			// Time_STOP에 0을 입력
	}
	
	sei();						// 전체 인터럽트를 허용
}

int main(void)
{
	DDRA = 0xff;		// 포트A를 출력포트로 설정
	DDRE = 0x00;		// 포트E를 입력포트로 설정
	TCCR2 = 0x05;		// 프리스케일러 1024
	OCR2 = 72;			// 0.01초 마다 한번씩 인터럽트 발생
	TIMSK = 0x80;
	TIFR |=1 << OCF2;
	
	EICRB = 0x03;		// 인터럽트4를 상승엣지에서 동작하도록 설정
	EIMSK = 0x10;		// 인터럽트4를 허용
	EIFR = 0x10;		// 인터럽트4 플래그를 클리어
	
	sei();
	
	while (1)
	{
		PORTA = FND_DATA_TBL[time_s];		// 포트A에 FND Table 값을 출력
	}
	
	return 0;
}