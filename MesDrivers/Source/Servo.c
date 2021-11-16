#include "stm32f10x.h"
#include "MyTimer.h"
#include "PWM.h"
#include "stdlib.h"


void angle_servo(int alpha, TIM_TypeDef * MyTimer){
	if (alpha < 45 || alpha > 315){
		PWM_RapportCyclique(MyTimer, 6000);
	} else {
		if (alpha < 180){
			int beta = (300/9)*((4*alpha)/6 - 30) + 3000;
			PWM_RapportCyclique(MyTimer, beta);
		}else {
			int beta = (300/9)*((4*abs(alpha-360))/6 - 30) + 3000;
			PWM_RapportCyclique(MyTimer, beta);
		}
	}
}
