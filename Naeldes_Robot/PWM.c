


#include <stdlib.h>
#include <avr/io.h>

#include "uart_int.h" // TODO remove

int PWM_Initiation_Timer0();
int PWM_Initiation_Timer2();

int PWM_Set_Duty_Uptime_Timer0(uint8_t uptime);
int PWM_Set_Duty_Uptime_Timer2(uint8_t uptime);

void PWM_Initiation()
{
	PWM_Initiation_Timer0();
	PWM_Initiation_Timer2();
}

void Set_Left_Motor_Speed(uint8_t percentage)
{
	// 255/100 = 2.55
	uint16_t uptime = 2.55 * (double)percentage;
	PWM_Set_Duty_Uptime_Timer0(uptime);
}

void Set_Right_Motor_Speed(uint8_t percentage)
{
	// 255/100 = 2.55
	uint16_t uptime = 2.55 * (double)percentage;
	PWM_Set_Duty_Uptime_Timer2(uptime);
}



int PWM_Initiation_Timer0()
{
	// D6/PD6
	//DDRD |= 1<<6; // Set pin to output
	DDRD  &= ~(1<<6); // Set pin to input, to turn it off to start with.
	
	// WGM ( Waveform Generation Mode ) 00-02 : Set to 011 for fast PWM mode
	// Timer/Counter0 Control Register A
	TCCR0A |=	1<<WGM00;  // 1
	TCCR0A |=	1<<WGM01;  // 1
	// Timer/Counter0 Control Register B
	TCCR0B &= ~(1<<WGM02); // 0
	
	// COM ( Compare Output Mode ) 0-1 : Set to 10 to for non-inverted signal
	// Timer/Counter0 Control Register A
	TCCR0A &= ~(1<<COM0A0); // 0
	TCCR0A |=	1<<COM0A1;  // 1

	OCR0A = 1; // start at 1/255th

	// CCS, IE Clock Select 00-02 : Set to 001 for no pre-scaling. Since it is for LED's, we want as high a frequency as possible.
	// This starts the timer
	// Timer/Counter0 Control Register A
	TCCR0B |=	1<<CS00;  // 1
	TCCR0B &= ~(1<<CS01); // 0
	TCCR0B &= ~(1<<CS02); // 0
	
	return 0;
}


int PWM_Set_Duty_Uptime_Timer0(uint8_t uptime)
{
	if(uptime == 0)
	{
		DDRD  &= ~(1<<6);
		return 0;
	}
	else
	{
		DDRD |= 1<<6;
	}
	
	OCR0A = uptime;
	return 0;
}

int PWM_Initiation_Timer2()
{
	// D11/PB3
	DDRB |= 1<<3; // Set pin to output
	
	// WGM ( Waveform Generation Mode ) 00-02 : Set to 011 for fast PWM mode
	// Timer/Counter0 Control Register A
	TCCR0A |=	1<<WGM00;  // 1
	TCCR0A |=	1<<WGM01;  // 1
	// Timer/Counter0 Control Register B
	TCCR0B &= ~(1<<WGM02); // 0
	
	
	// WGM ( Waveform Generation Mode ) 20-22 : Set to 011 for fast PWM mode
	// Timer/Counter0 Control Register A
	TCCR2A |=	1<<WGM20;  // 1
	TCCR2A |=	1<<WGM21;  // 1
	// Timer/Counter0 Control Register B
	TCCR2B &= ~(1<<WGM22); // 0

	// COM ( Compare Output Mode ) 0-1 : Set to 10 to for non-inverted signal
	// Timer/Counter2 Control Register A
	TCCR2A &= ~(1<<COM2A0); // 0
	TCCR2A |=	1<<COM2A1;  // 1

	OCR2A = 1; // start at 1/255th

	// CCS, IE Clock Select 20-22 : Set to 001 for no pre-scaling.
	// Since it is for LED's, we want as high a frequency as possible.
	// This starts the timer
	// Timer/Counter2 Control Register A
	TCCR2B |=	1<<CS20;  // 1
	TCCR2B &= ~(1<<CS21); // 0
	TCCR2B &= ~(1<<CS22); // 0
	
	return 0;
}

int PWM_Set_Duty_Uptime_Timer2(uint8_t uptime)
{
	if(uptime == 0)
	{
		DDRB  &= ~(1<<3);
		return 0;
	}
	else
	{
		DDRB |= 1<<3;
	}
	
	OCR2A = uptime;
	return 0;
}