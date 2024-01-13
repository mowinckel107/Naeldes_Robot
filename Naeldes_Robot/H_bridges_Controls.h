


#ifndef H_BRIDGES_CONTROLS_H_
#define H_BRIDGES_CONTROLS_H_


void H_Bridges_Initialize();

void H_Bridge_1_Set_Direction_Forward();
void H_Bridge_2_Set_Direction_Forward();

void H_Bridge_1_Set_Direction_Backwards();
void H_Bridge_2_Set_Direction_Backwards();

void H_Bridge_1_Turn_Off();
void H_Bridge_2_Turn_Off();

#endif /* H_BRIDGES_CONTROLS_H_ */