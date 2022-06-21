/*
 * LCD.c
 *
 * Created: 2022-06-20 오후 2:53:58
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"


int main(void)
{
	Byte *str1 = "LCD TEST";		// 포인트 문자열1
	Byte *str2 = "ATmage 128";		// 포인트 문자열2
	
    DDRA = 0x0f;
	
	Lcd_Init();						// LCD 초기화
	Lcd_Clear();
	
    while (1) 
    {
		Lcd_Pos(0, 0);				// LCD 위치설정 (위쪽)
		Lcd_STR(str1);				// LCD에 문자열1 출력
		Lcd_Pos(1, 0);				// LCD 위치설정 (아래쪽)
		Lcd_STR(str2);				// LCD에 문자열2 출력
    }
	
	return 0;
}

