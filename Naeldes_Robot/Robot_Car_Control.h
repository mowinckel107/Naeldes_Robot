

#ifndef ROBOT_CAR_CONTROL_H_
#define ROBOT_CAR_CONTROL_H_

#include "uart_int.h"
#include "Button_Interrupts.h"
#include <stdbool.h>


#define SPEED 50

void Robot_Initialize();

void Robot_Drive_Forward();
void Robot_Drive_Backwards();
void Robot_Turn_Left();
void Robot_Turn_Right();
void Robot_Stop();


#endif /* ROBOT_CAR_CONTROL_H_ */