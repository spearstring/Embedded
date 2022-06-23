/*
 * PIEZOTest3.c
 *
 * Created: 2022-06-23 오전 11:04:34
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>				// AVR 입출력에 대한 헤더 파일
#include <util/delay.h>			// delay 함수사용을 위한 헤더 파일

// 피아노 음계에 해당하는 PWM 주파수
unsigned int DoReMi[8] = {523, 587, 659, 698, 783,880, 987, 1046};
volatile char TX_data = 0;		// 전송 값 저장 변수

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);		// 전송준비 될때까지 대기
	UDR0 = data;		// 데이터를 UDR0에 쓰면 전송
	UCSR0A |= 0x20;
}

unsigned char getch(void)
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);		// 데이터를 받을때까지 대기
	data=UDR0;		// 수신되 데이터는 UDR0에 저장
	UCSR0A |= 0x80;
	return data;		// 읽어온 문자를 변환
}

int main(void)
{
	unsigned char RX_data =0;
	
	DDRE = 0xfe;
	DDRB = 0x80;		// PWM 출력
	
	UCSR0A = 1 << MPCM0;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	TCCR3A = 1 << WGM30;		// WGM3(1:0) = "00"
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30);		// WGM3 (3:2) = "11", CS3(2:0) = "001" 1분주 사용
	TCCR3C = 0x00;		// WGM3(3:0) = "1110", Fast PWM, 모드 14
	TCNT3 = 0x0000;		// 타이머3 카운터 초기화
	
	while(1)
	{
		//putch(getch());
		RX_data = getch();		// PC로 부터 입력받은 데이터를 변수 RX_data에 저장
		if ((RX_data >= 0x30) && (RX_data < 0x39))
		{
			ICR3 = 7372800 / DoReMi[RX_data - 0x30];		// 버튼에 맞는 음향을 연주
			OCR3C = ICR3 / 8;
			TCCR3A = 1 << COM3A0;
			_delay_ms(500);
			TCCR3A = 1 << WGM30;		// 부저 소리 끈다
		}
	}
	
}
