/*
 * interrupt3.c
 *
 * Created: 2022-06-20 오전 11:22:45
 *  Author: PKNU
 */ 
#define  F_CPU 7432800UL
#include <avr/io.h>				// AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>		// 인터럽트 관련 시스템 헤더 파일
#include <util/delay.h>			// delay 함수사용을 위한 헤더파일

volatile unsigned char exchange = 0;

SIGNAL(INT4_vect)				// 인터럽트 서비스 루틴
{
	cli();						// 전체 인터럽트를 금지
	if (exchange == 0)			// Time_Stop이 0인 경우
	{
		exchange = 1;			// Time_Stop에 1을 입력
	}
	else                        // Time_Stop이 1인 경우
	{
		exchange = 0;			// Time_Stop에 0을 입력
	}
	sei();						// 전체 인터럽트를 허용
}

int main()
{
	unsigned char LED_Data = 0x01;
	DDRE = 0x00;				// 포트E 를 입력포트로 설정
	DDRA = 0xff;				// 포트A 를 출력포트로 설정
	EIMSK = 0x10;				// 인터럽트 4를 허용
	EICRB = 0x03;				// 인터럽트 4를 상승엣지에서 동작하도록 설정
	EIFR = 0x10;				// 인터럽트 4 플래그를 클리어
	sei();						// 전체 인터럽트를 허용
	
	
	while (1)
	{
		PORTA = LED_Data;				// 포트C로 변수 LED_Data에 있는 데이타 출력
		if (exchange == 0)				// exchange가 0인 경우
		{
			if (LED_Data == 0x80)		// LED_Data 값이 0x80이면 LED_Data 값을 0x01로 함
			{
				LED_Data = 0x01;
			}
			else LED_Data <<= 1;		// LED_Data 값을 왼쪽으로 쉬프트
		}
		_delay_ms(500);
	}
	
	return 0;
}