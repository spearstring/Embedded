/*
 * testUART3.c
 *
 * Created: 2022-06-21 오전 11:19:01
 *  Author: PKNU
 */ 
#include <avr/io.h>			// AVR 입출력에 대한 헤더 파일

void putch(unsigned char data)
{
	while ((UCSR0A & 0x20) == 0);		// 전송 준비 될때까지 대기
	{
		UDR0 = data;					// 데이터를 UDR0에 쓰면 전송
		UCSR0A |= 0x20;
	}
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);		// 데이터를 받을 때까지 대기
	data = UDR0;						// 수신된 데이터는 UDR0에 저장
	UCSR0A |= 0x80;						
	return data;						// 읽어온 문자를 변환
	
}

int main(void)
{
	unsigned char text[] = "\r\nWelcome! edgeiLAB\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
	
	DDRE = 0xfe;		// Rx(입력 0), Tx(출력, 1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;		// Rx, Tx enable
	UCSR0C = 0x06;		// 비동기 방식, No Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3;			// 115200 bps
	
	while (text[i]!='\0')		// 문자열 데이터가 '\0'인 경우, 문자열 끝임
	{
		putch(text[i++]);		// 저장된 text 문자열을 출력
	}
	
	i = 0;						// 카운터변수 초기화
	
	while (echo[i]!='\0')		// 문자열 데이터가 '\0'인 경우, 문자열 끝임
	{
		putch(echo[i++]);		// 저장된 echo 문자열을 출력
	}
	while(1)
	{
		putch(getch());			// getch()로 입력받은 문자를 다시 putch()로 문자열 출력
	}
}