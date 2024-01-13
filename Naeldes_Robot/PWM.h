


#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void PWM_Initiation();

void Set_Left_Motor_Speed(uint8_t percentage);
void Set_Right_Motor_Speed(uint8_t percentage);


#endif /* PWM_H_ */