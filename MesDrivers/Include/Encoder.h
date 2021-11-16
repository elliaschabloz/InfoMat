/*
Encoder.h
-----
*/
#ifndef Encoder_H
#define Encoder_H
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

void MyTimer_Encoder_Init(TIM_TypeDef * Timer);
void MyZero_ActiveIT(char Prio);
void EXTI0_IRQHandler (void);

#endif
