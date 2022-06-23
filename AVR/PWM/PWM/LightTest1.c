/*
 * PWM.c
 *
 * Created: 2022-06-22 오후 4:24:18
 * Author : PKNU
 */ 
#define F_CPU 7372800
#include <avr/io.h>				// AVR 입출력에 대한 헤더 파일
#include <util/delay.h>		// delay 함수사용을 위한 헤더파일


int main(void)
{
    unsigned char Light = 0;
	
	DDRB = 0x10;				// 포트B 를 출력포트로 설정
	
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00) | (1 << CS02) | (1 << CS01);		// PC PWM 모드, 256 분주 ==> 7200Hz :
	TCNT0 = (1 << TCNT0);		// 타이머0 카운터를 초기화
	
    while (1) 
    {
		for (Light = 0; Light < 255 ; Light++)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
		for (Light = 255; 0 < Light; Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
    }
}

