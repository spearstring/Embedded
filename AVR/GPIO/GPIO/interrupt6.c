/*
 * interrupt.c
 *
 * Created: 2022-06-20 오후 12:31:05
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>							// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>					// AVR 인터럽트에 대한 헤더파일
#include <util/delay.h>						// delay 함수사용을 위한 헤더파일

volatile unsigned char Time_STOP = 0;
volatile unsigned char cnt = 0;				// FND Table 카운터 변수

SIGNAL(INT4_vect)		// 인터럽트 서비스 루틴
{
	cli();				// 전체 인터럽트를 금지
	Time_STOP = 1;		// Time_Stop에 1을 입력
	cnt = 0;			// FND Table 카운터 변수 값을 초기화
	sei();				// 전체 인터럽트를 허용
};

SIGNAL(INT6_vect)		// 인터럽트 서비스 루틴
{
	cli();				// 전체 인터럽트를 금지
	Time_STOP = 0;		// Time_Stop에 0을 입력
	sei();				// 전체 인터럽트를 허용
};

int main()
{
	// 7-Segment에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL [] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
									0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c,
									0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	DDRA = 0xff;								// 포트A 를 출력포트로 설정
	DDRE = 0x00;								// 포트E 를 입력포트로 설정
	EICRB = (1 << ISC41) | (1 << ISC61);		// 인터럽트 4를 하강엣지, 6을 상승엣지에서 동작하도록 설정
	EIMSK = (1 << INT4) | (1 << INT6);			// 인터럽트 4, 6을 허용
	EIFR = (1 << INT4) | (1 << INT6);			// 인터럽트 4, 6 플래그를 클리어
	sei();										// 전체 인터럽트를 허용
	
	while (1)
	{
		PORTA = FND_DATA_TBL[cnt];				// 포트A에 FND Table 값을 출력
		if (Time_STOP == 0)						// Time_Stop이 0인 경우
		{
			cnt++;								// FND Table 카운터 변수를 증가
			if (cnt > 17)						// 테이블 크기를 초과하는 경우 방지
			{
				cnt=0;
			}
		}
		_delay_ms(200);
	}
	
	return 0;
}