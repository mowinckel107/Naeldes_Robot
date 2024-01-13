


#ifndef BUTTON_INTERRUPTS_H_
#define BUTTON_INTERRUPTS_H_


void Button_Interrupts_Initialize();

void Set_Button_1_Function( void ( *Button_Function )() );
void Set_Button_2_Function( void ( *Button_Function )() );

#endif /* BUTTON_INTERRUPTS_H_ */