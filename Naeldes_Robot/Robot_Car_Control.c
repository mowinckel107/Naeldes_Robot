

#include "Robot_Car_Control.h"

#include "H_bridges_Controls.h"
#include "PWM.h"
#include "Button_Interrupts.h"




void Robot_Initialize()
{
	InitUART(9600, 8, 'N', 1);
	Button_Interrupts_Initialize();
	H_Bridges_Initialize();
	PWM_Initiation();
}

void Robot_Drive_Forward()
{
	Set_Left_Motor_Speed(SPEED);
	Set_Right_Motor_Speed(SPEED);
	
	H_Bridge_1_Set_Direction_Forward();
	H_Bridge_2_Set_Direction_Forward();
}

void Robot_Drive_Backwards()
{
	Set_Left_Motor_Speed(SPEED);
	Set_Right_Motor_Speed(SPEED);
	
	H_Bridge_1_Set_Direction_Backwards();
	H_Bridge_2_Set_Direction_Backwards();
}

void Robot_Turn_Left()
{
	Set_Left_Motor_Speed(SPEED);
	Set_Right_Motor_Speed(SPEED);
	
	H_Bridge_1_Set_Direction_Backwards();
	H_Bridge_2_Set_Direction_Forward();
}

void Robot_Turn_Right()
{
	Set_Left_Motor_Speed(SPEED);
	Set_Right_Motor_Speed(SPEED);
	
	H_Bridge_1_Set_Direction_Forward();
	H_Bridge_2_Set_Direction_Backwards();
}

void Robot_Stop()
{
	Set_Left_Motor_Speed(0);
	Set_Right_Motor_Speed(0);
	
	H_Bridge_1_Turn_Off();
	H_Bridge_2_Turn_Off();
}
