
#include <avr/io.h>
#include <avr/interrupt.h>


static void emptyDefaultFunction(){}

static void (*Button_1_Callback_Function_Pointer)() = emptyDefaultFunction;
static void (*Button_2_Callback_Function_Pointer)() = emptyDefaultFunction;



void Button_Interrupts_Initialize()
{
	DDRD &= ~(1<<2);
	DDRD &= ~(1<<3);
	
	// ISC0 Set to 10 to generate interrupt at falling edge for INT0
	EICRA |=   1<<ISC01;
	EICRA &= ~(1<<ISC00);
	
	// ISC1 Set to 10 to generate interrupt at falling edge for INT1
	EICRA |=   1<<ISC11;
	EICRA &= ~(1<<ISC10);
	
	EIMSK |=   1<<INT0; // Enable INT0
	EIMSK |=   1<<INT1; // Enable INT1
	sei();
}

void Set_Button_1_Function( void ( *Button_Function )() )
{
	Button_1_Callback_Function_Pointer = Button_Function;
}

void Set_Button_2_Function( void ( *Button_Function )() )
{
	Button_2_Callback_Function_Pointer = Button_Function;
}

ISR(INT0_vect)
{
	Button_1_Callback_Function_Pointer();
	EIFR |= 1<<INTF0; // Set INT0 interrupt flag to 1, to disable it, if button have been registering multiple presses
}

ISR(INT1_vect)
{
	Button_2_Callback_Function_Pointer();
	EIFR |= 1<<INTF1; // Set INT1 interrupt flag to 1, to disable it, if button have been registering multiple presses
}