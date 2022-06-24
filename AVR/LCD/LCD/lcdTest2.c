/*
 * lcdTest2.c
 *
 * Created: 2022-06-20 오후 4:15:19
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"


int main(void)
{	
	Byte buf[20];			// 구구단을 담을 배열
	
	DDRF = 0xff;
	DDRG = 0x0f;
	
	Lcd_Init();
	Lcd_Clear();
	
	while (1)
	{
		for (int i = 2; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				Lcd_Pos(0,0);
				sprintf(buf, "%d x %d = %d", i, j, i * j);		// sprintf를 이용하여 buf에 담고 구구단 출력
				Lcd_STR(buf);
				_delay_ms(700);
				Lcd_Clear();
			}
		}
	}
	
	return 0;
}
