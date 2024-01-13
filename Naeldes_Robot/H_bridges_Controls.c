
#include "H_bridges_Controls.h"

#include <avr/io.h>


void H_Bridge_1_Initialize();
void H_Bridge_2_Initialize();


void H_Bridges_Initialize()
{
	H_Bridge_1_Initialize();
	H_Bridge_2_Initialize();
}

void H_Bridge_1_Initialize()
{
	PORTD &= ~(1<<7);
	PORTB &= ~(1<<0);
	PORTB &= ~(1<<1);
	PORTB &= ~(1<<2);
	
	DDRD |= 1<<7;
	DDRB |= 1<<0;
	DDRB |= 1<<1;
	DDRB |= 1<<2;
}

void H_Bridge_2_Initialize()
{
	PORTC &= ~(1<<3);
	PORTC &= ~(1<<2);
	PORTC &= ~(1<<1);
	PORTC &= ~(1<<0);
	
	DDRC |= 1<<3;
	DDRC |= 1<<2;
	DDRC |= 1<<1;
	DDRC |= 1<<0;
}
	
void H_Bridge_1_Set_Direction_Forward()
{
	H_Bridge_1_Turn_Off();
	
	PORTB |=   1<<0;
	PORTB |=   1<<2;
}

void H_Bridge_2_Set_Direction_Forward()
{
	H_Bridge_2_Turn_Off();
	
	PORTC |=   1<<2;
	PORTC |=   1<<0;
}

void H_Bridge_1_Set_Direction_Backwards()
{
	H_Bridge_1_Turn_Off();
	
	PORTD |=   1<<7;
	PORTB |=   1<<1;
}

void H_Bridge_2_Set_Direction_Backwards()
{
	H_Bridge_2_Turn_Off();
	
	PORTC |=   1<<3;
	PORTC |=   1<<1;
}

void H_Bridge_1_Turn_Off()
{
	PORTD &= ~(1<<7);
	PORTB &= ~(1<<0);
	PORTB &= ~(1<<1);
	PORTB &= ~(1<<2);
}

void H_Bridge_2_Turn_Off()
{
	PORTC &= ~(1<<0);
	PORTC &= ~(1<<1);
	PORTC &= ~(1<<2);
	PORTC &= ~(1<<3);
}