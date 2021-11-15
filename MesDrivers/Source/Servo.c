#include "stm32f10x.h"
#include "MyTimer.h"
#include "stdlib.h"

void angle_servo(int alpha, TIM_TypeDef * MyTimer){
	if (abs(alpha) < 45){
		PWM_RapportCyclique(MyTimer, 6000);
	} else {
		int beta = (300/9)*((4*alpha)/6 - 30) + 3000;
		PWM_RapportCyclique(MyTimer, beta);
	}
}
