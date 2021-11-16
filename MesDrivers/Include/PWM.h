/*
PWM.h
-----
*/
#ifndef PWM_H
#define PWM_H
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

void MyTimer_PWM(TIM_TypeDef * Timer, int Channel);
void PWM_RapportCyclique(TIM_TypeDef * Timer, int alpha);
void PWM_Port_Init(int Timer_number, int Channel);

#endif
