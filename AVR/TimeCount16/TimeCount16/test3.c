/*
 * test3.c
 *
 * Created: 2022-06-22 오후 12:19:51
 *  Author: PKNU
 */ 
#include <avr/io.h>					// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>			// AVR 인터럽트에 대한 헤더파일

// 7-Segment에 표시할 글자의 입력 데이터 저장
unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c,
								0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e,
								0x79, 0x71, 0x08, 0x80};
								
volatile unsigned char time_s = 0;		//초를 세는 변수
volatile unsigned char FND_flag = 0, edge_flag = 0;

SIGNAL(TIMER3_CAPT_vect)
{
	cli();
	
	unsigned int count_check;
	
	// 스위치가 눌릴 시간 측정을 위해
	// 상승에지에서 하강에지까지의 시간을 계산
	
	if (edge_flag == 0)		// 상승 에지(스위치를 누르면)
	{
		TCCR3B = (1 << CS32) | (1 << CS30);		// 프리스케일러 1024, 하강에지 캡처 트리거 설정
		TCNT3 = 0;			// TCNT3 레지스터를 0으로 초기화
		ICR3 = 0;			// ICR3 레지스터를 0으로 초기화
		edge_flag = 1;
	}
	else                    // 하강 에지(스위치를 떼면)
	{
		TCCR3B = (1 << ICES3) | (1 << CS32) | (1 << CS30);		// 프리스케일러 1024, 상승에지 캡처 트리거 설정
		count_check = ICR3;
		
		// 7372800 / 1024 = 7200 Hz, 1초동안 TCNT의 값은 7200
		time_s = count_check / 720;		// 누를 시간을 0.1초 단위로 변경
		
		// 측정 시간 FND로 출력 0~ 1.5초 까지 측정 가능
		FND_flag = 1;
		edge_flag = 0;
	}
	sei();
}

int main(void)
{
	DDRA = 0xff;				// 포트A를 출력포트로 설정
	DDRE = 0x00;				// 포트E를 입력포트로 설정
	
	TCCR3A = 1 << COM3C0;
	TCCR3B = (1 << ICES3) | (1 << CS32) | (1 << CS30);				// 프리스케일러 1024, 상승에지 캡처 트리거 설정
	ETIMSK = 1 << ICF3;			// 입력캡처 인터럽트3 활성화
	ETIFR |=1 << ICF3;
	
	sei();
	
	PORTA = FND_DATA_TBL[0];	// 포트A에 FND Table의 값을 출력
	while (1)
	{
		if (FND_flag)
		{
			if (time_s > 15)	// 최대 1.5초까지 표시(F)
			{
				time_s = 15;
			}
			
			PORTA = FND_DATA_TBL[time_s];		// 포트A에 FND Table 값 출력
			FND_flag = 0;
		}
	}
	return 0;
}