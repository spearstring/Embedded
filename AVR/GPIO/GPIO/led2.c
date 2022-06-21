/*
 * led2.c
 *
 * Created: 2022-06-17 오후 1:55:18
 *  Author: PKNU
 */ 
#define  F_CPU 7432800
#include <avr/io.h>		// AVR 입출력에 대한 헤더 파일
#include <util/delay.h>		// delay 함수사용을 위한 헤더파일

int main()
{
	unsigned char LED_Data = 0xFF, i;
	DDRA = 0xFF;	// 포트A를 출력포트로 설정
	
	while (1)
	{
		LED_Data = 0xFF;	// 변수 LED_Data에 초기값 0xFF로 저장
		for (i=0; i < 9; i++)
		{
			PORTA = LED_Data;	// 포트A로 변수 LED_Data에 있는 데이터 출력
			LED_Data <<=1;		// 좌측 쉬프트 연산자를 이용
			PORTA = 0xFF;
			_delay_ms(1000);	// ms 단위의 딜레이 함수
		}
	}
	
	return 0;
}