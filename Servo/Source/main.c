#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


#define TIMER_ARR 59999
#define TIMER_PSC 24

//CNT2 = (340/9)*(CNT/6 - 30) + 3400
MyTimer_Struct_TypeDef MyTimer;


void Callback(void){
}



int main(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	MyTimer.Timer = TIM3;
	MyTimer.ARR = TIMER_ARR;
	MyTimer.PSC = TIMER_PSC;
	MyTimer.Timer_num = 3;
	
	MyTimer_Base_Init(&MyTimer);
	MyTimer_Base_Start(&MyTimer);
	PWM_Port_Init(3, 3);
	
	
	MyTimer_PWM(MyTimer.Timer, 3);
	
	
	
	do{
		//PWM_RapportCyclique(MyTimer.Timer, 3600);
		PWM_RapportCyclique(MyTimer.Timer, 4500);
		//PWM_RapportCyclique(MyTimer.Timer, 6400);
		
	}while(1);	
}
