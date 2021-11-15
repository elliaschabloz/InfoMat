#ifndef SERVO_H
#define SERVO_H
#include "stm32f10x.h"
#include "MyTimer.h"

void angle_servo(int alpha, TIM_TypeDef * Timer);

#endif
