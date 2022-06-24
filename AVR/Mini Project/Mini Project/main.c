/*
 * Mini Project.c
 *
 * Created: 2022-06-24 오전 9:37:22
 * Author : PKNU
 */ 
#define  F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "Lcd.h"

void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000
	PORTA = 0x07; //0b 0000 0111
}

unsigned char keyscan()
{
	PORTA = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '1';
	else if((PINA & 0x07) == 0x02) return '2';
	else if((PINA & 0x07) == 0x04) return '3';
	_delay_ms(10);
	
	PORTA = 0x10;		// 0x10
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '4';
	else if((PINA & 0x07) == 0x02) return '5';
	else if((PINA & 0x07) == 0x04) return '6';
	_delay_ms(10);
	
	PORTA = 0x20;		// 0x20
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '7';
	else if((PINA & 0x07) == 0x02) return '8';
	else if((PINA & 0x07) == 0x04) return '9';
	_delay_ms(10);
	
	PORTA = 0x40;		// 0x40
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '*';
	else if((PINA & 0x07) == 0x02) return '0';
	else if((PINA & 0x07) == 0x04) return '#';
	_delay_ms(10);
	
	return 0;
}

void putch(unsigned char data) 
{
	while((UCSR0A & 0x20) == 0); // 전송 준비가 될 때까지 대기
	UDR0 = data; // 데이터를 UDR0에 쓰면 전송
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0); // 데이타를 받을 때까지 대기
	data=UDR0; // 수신된 데이터는 UDR0에 저장
	UCSR0A |= 0x80;
	return data; // 읽어온 문자를 반환
}

// 피아노 음계에 해당하는 PWM 주파수
unsigned int Pass[4] = {523, 659, 783, 1046};
unsigned int NonPass[4] = {659, 523, 659, 523};

// 비밀번호 저장 배열
unsigned char password[4] = {'1', '2', '3', '4'};
	
unsigned int p = 0;		// 비밀번호가 맞을 경우 카운팅
unsigned int w = 0;		// 비밀번호가 틀릴 경우 카운팅
	
volatile char TX_data = 0; // 스위치 전송 값 저장 변수

int main(void)
{
	unsigned char i, t = 0;
	
	unsigned char piano = 0;
	
	DDRB = 0x20;
	PORTB &= ~0x20;
	DDRC = 0xf0;
	DDRE = 0xfe;
	DDRF = 0xff;
	DDRG = 0x0f;
	
	TCCR3A = 1 << WGM30;		// WGM3(1:0) = "00"
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30);		// WGM3 (3:2) = "11", CS3(2:0) = "001" 1분주 사용
	TCCR3C = 0x00;											// WGM(3:0)="1110", Fast PWM, 모드 14
	TCNT3 = 0x0000;
	
	UCSR0A = 1 << MPCM0;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	EICRB = 1 << ISC41;
	ETIMSK = 1 << INT4;
	EIFR = 1 << INTF4;
	
	init_keypad();
	
	Lcd_Init();
	Lcd_Clear();
	
	Byte *str1 = "Doorlock system";
	Byte str2[] = "Insert PW:";
	Byte *str3 = "OPEN DOOR";
	Byte *str4 = "RETRY!!";
	Byte *str5 = "*";
	
	Lcd_Pos(0,0);
	Lcd_STR(str1);
	
	Lcd_Pos(1,0);
	Lcd_STR(str2);
	
	while (1)
	{
		init_keypad();
		
		unsigned char key = keyscan();
		if ((key >= '0' && key <='9') || (key == '*') || (key == '#'))
		{
			init_keypad();
			
			Lcd_Init();
			strcat(str2, str5);
			Lcd_Pos(0,0);
			Lcd_STR(str1);
			Lcd_Pos(1,0);
			Lcd_STR(str2);
		
			if (key == password[p])
			{	
				_delay_ms(100);
				p++;
				w = 0;
			}	
			
			else if (key != password[p])
			{
				_delay_ms(100);
				p = 0;
				w++;
			}
			
			if (p == 4)
			{	
				init_keypad();
				
				Lcd_Clear();
				Lcd_Pos(1,0);
				Lcd_STR(str3);
				
				p = 0;
				
				DDRB = 0x80;		// PWM출력, OCR1C
				ICR3 = 7372800 / Pass[piano];						// 버튼에 맞는 음향을 연주
				OCR3C = ICR3 / 4 ;									// 50% 듀티비
				TCCR3A = 1 << COM3A0;
				piano++;											// piano 변수 1증가
				_delay_ms(500);
				TCCR1A = 1 << WGM30;
				
				for (i = 0; i < 5; i++)
				{
					PORTC = 0x30; // 1 step
					_delay_ms(10);
					PORTC = 0x90; // 2 step
					_delay_ms(10);
					PORTC = 0xC0; // 3 step
					_delay_ms(10);
					PORTC = 0x60; // 4 step
					_delay_ms(10);
					PORTC = 0;
				}
				_delay_ms(1000000);
				
			}
			
			if (w == 4)
			{
				init_keypad();
			
				Lcd_Clear();
				Lcd_Pos(1,0);
				Lcd_STR(str4);
			
				w = 0;
				
				ICR3 = 7372800 / NonPass[piano];						// 버튼에 맞는 음향을 연주
				OCR3C = ICR3 / 8 ;									// 50% 듀티비
				TCCR3A = 1 << COM3A0;
				piano++;											// piano 변수 1증가
				_delay_ms(500);
				TCCR3A = 1 << WGM30;
			}
		}
	}

	return 0;
}

