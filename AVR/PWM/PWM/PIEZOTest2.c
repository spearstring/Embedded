/*
 * PIEZOTest2.c
 *
 * Created: 2022-06-23 오전 10:10:56
 *  Author: PKNU
 */ 
#define  F_CPU 7372800
#include <avr/io.h>				// AVR 입출력에 대한 헤더 파일
#include <util/delay.h>			// delay 함수사용을 위한 헤더 파일
#include <avr/interrupt.h>		// AVR 인터럽트 사용을 위한 헤더 파일

// 피아노 음계에 해당하는 PWM 주파수
unsigned int DoReMi[8] = {523, 587, 659, 698, 783,880, 987, 1046};
volatile unsigned char sound_flag = 1;

int main(void)
{
	DDRD = 0x00;		// 포트D를 입력포트로 설정
	DDRE = 0x08;		// 포트E PE3을 출력 나머지는 입력포트로 설정
						// Buzzer를 PE3에 연결
						
	TCCR3A = 1 << WGM30;		// WGM3(1:0) = "00"
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30);		// WGM3 (3:2) = "11", CS3(2:0) = "001" 1분주 사용
	TCCR3C = 0x00;		// WGM3(3:0) = "1110", Fast PWM, 모드 14
	TCNT3 = 0x0000;		// 타이머3 카운터 초기화
	
	EICRA = (1 << ISC01) | (1 << ISC11) | (1 << ISC21) | (1 << ISC31);		// 인터럽트 0, 1, 2, 3을 상승엣지에서 동작하도록 설정
	EICRB = (1 << ISC41) | (1 << ISC51) | (1 << ISC61) | (1 << ISC71);		// 인터럽트 4, 5, 6, 7을 상승엣지에서 동작하도록 설정
	EIMSK = (1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3) | (1 << INT4) | (1 << INT5) | (1 << INT6) | (1 << INT7);		// 인터럽트 0, 1, 2, 3, 4, 5, 6, 7을 허용
	EIFR = (1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3) | (1 << INT4) | (1 << INT5) | (1 << INT6) | (1 << INT7);		// 인터럽트 0, 1, 2, 3, 4, 5, 6, 7 플래그를 클리어
	
	sei();
	
	while(1)
	{
		if (sound_flag)
		{
			_delay_ms(300);		// 2초지연
			TCCR3A = 1 << WGM30;		// 부저 소리 끈다
			sound_flag = 0;
		}
	}
}

SIGNAL(INT0_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[0] / 2;		// 도의 음향을 연주
	TCCR3A = 1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT1_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[1] / 2;		// 레의 음향을 연주
	TCCR3A = 1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT2_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[2] / 2;		// 미의 음향을 연주
	TCCR3A = 1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT3_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[3] / 2;		// 파의 음향을 연주
	TCCR3A = 1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT4_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[4] / 2;		// 솔의 음향을 연주
	TCCR3A = 0x40; //1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT5_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[5] / 2;		// 라의 음향을 연주
	TCCR3A = 0x40; //1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT6_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800 / DoReMi[6] / 2;		// 시의 음향을 연주
	TCCR3A = 0x40; //1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}

SIGNAL(INT7_vect)		// 인터럽트 서비스 루틴
{
	cli();		// 전체 인터럽트를 금지
	ICR3 = 7372800  /DoReMi[7] / 2;		// 도의 음향을 연주
	TCCR3A = 0x40; //1 << COM3A0;		// PE4로 출력
	sound_flag = 1;		// 부저음이 발생하도록 설정
	sei();
}