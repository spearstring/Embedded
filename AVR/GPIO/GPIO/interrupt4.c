/*
 * interrupt4.c
 *
 * Created: 2022-06-20 오전 11:48:42
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL					
#include <avr/io.h>								// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>						// AVR 인터럽트에 대한 헤더파일
#include <util/delay.h>							// delay 함수사용을 위한 헤더파일

volatile unsigned char Shift_flag = 1;

SIGNAL(INT5_vect)								// 인터럽트 서비스 루틴
{
	cli();										// 전체 인터럽트를 금지
	Shift_flag = 1;								// Shift_flag에 1을 입력
	sei();										// 전체 인터럽트를 허용
}

SIGNAL(INT7_vect)								// 인터럽트 서비스 루틴
{
	cli();										// 전체 인터럽트를 금지
	Shift_flag = 2;								// Shift_flag에 2를 입력
	sei();										// 전체 인터럽트를 허용
}

int main()
{
	unsigned char LED_Data = 0x01;
	DDRE = 0x00;								// 포트E 를 입력포트로 설정
	DDRA = 0xff;								// 포트A 를 출력포트로 설정
	EICRB = (1 << ISC51) | (1 << ISC71);		// 인터럽트 5를 하강에지, 7을 상승에지에서 동작하도록 설정
	EIMSK = (1 << INT5) | (1 << INT7);			// 인터럽트 5, 7을 허용
	EIFR = (1 << INT5) | (1 << INT7);			// 인터럽트 5, 7 플래그를 클리어
	sei();										// 전체 인터럽트를 허용

	while (1)
	{
		PORTA = LED_Data;						//포트C로 변수 LED_Data에 있는 데이타를 출력
		if (Shift_flag == 1)
		{
			if (LED_Data == 0x80)				// LED0 ~ LED7으로 이동
			{
				LED_Data = 0x01;
			}
			else                                
			{
				LED_Data <<= 1;					// LED_Data 값을 왼쪽으로 쉬프트
			}
		}
		else if (Shift_flag == 2)				// LED7 ~ LED0으로 이동
		{
			if (LED_Data == 0x01)
			{
				LED_Data = 0x80;
			}
			else
			{
				LED_Data >>= 1;					// LED_Data 값을 오른쪽으로 쉬프트
			}
		}
		_delay_ms(300);
	}

	return 0;
}