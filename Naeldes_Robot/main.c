

#define F_CPU 16000000
#include <util/delay.h>

#include "Robot_Car_Control.h"

void Naeldes_Function_1(void);
void Naeldes_Function_2(void);

// Buttons: D2(Button 1) and D3(Button 2)
	
// PWM signal_1: D6 (Left Motor)
// PWM signal_2: D11 (Right Motor)

// H Bridge Control 1: D7, D8, D9, D10 (Top left, bottom left, top right, bottom right) (Left Motor)
// H Bridge Control 2: A3, A2, A1, A0 (Top left, bottom left, top right, bottom right) (Right Motor)


int main(void)
{
	Robot_Initialize();

	Set_Button_1_Function( Naeldes_Function_1 );
	Set_Button_2_Function( Naeldes_Function_2 );
	
    while (true) 
    {
		_delay_ms(1000);
	}
}


void Naeldes_Function_1(void)
{

}

void Naeldes_Function_2(void)
{

}
