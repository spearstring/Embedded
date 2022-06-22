/*
 * test4.c
 *
 * Created: 2022-06-22 오후 3:20:36
 *  Author: PKNU
 */ 
#include <avr/io.h>					// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>			// AVR 인터럽트에 대한 헤더파일

// 7-Segment에 표시할 글자의 입력 데이터 저장
unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c,
								0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e,
								0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s = 0;		//초를 세는 변수

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;						// 1초 후에 인터럽트 발생
	if (time_s >= 17)
	{
		time_s = 0;						// time_s 변수는 17까지만 증가
	}
	else                                // 17되면 0으로 초기화
	{
		time_s++;
	}
	
	sei();
}

int main(void)
{
	DDRA = 0xff;				// 포트A를 출력포트로 설정
	
	TCCR1A = 1 << WGM10;
	TCCR1B = (1 << CS12) | (1 << CS10);		// 프리스케일러 1024
	
	OCR1A = 7200;				// 1초마다 한번씩 인터럽트 발생
	TIMSK = OCIE1A;
	TIFR |=1 << OCF1A;
	
	sei();
	
	PORTA = FND_DATA_TBL[0];	// 포트A에 FND Table의 값을 출력
	while (1)
	{
		PORTA = FND_DATA_TBL[time_s];		// 포트A에 FND Table 값 출력
	}
	return 0;
}