#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Servo.h"

#define TIMER_ARR 59999
#define TIMER_PSC 24

//CNT2 = (340/9)*(CNT/6 - 30) + 3400
MyTimer_Struct_TypeDef MyTimer;


void Callback(void){
}



int main(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	MyTimer.Timer = TIM4;
	MyTimer.ARR = TIMER_ARR;
	MyTimer.PSC = TIMER_PSC;
	MyTimer.Timer_num = 4;
	
	MyTimer_Base_Init(&MyTimer);
	MyTimer_Base_Start(&MyTimer);
	PWM_Port_Init(4, 1);
	
	
	MyTimer_PWM(MyTimer.Timer, 1);
	
	
	
	do{
		//PWM_RapportCyclique(MyTimer.Timer, 6000);
		//angle_servo(180, MyTimer.Timer);
		angle_servo(180, MyTimer.Timer);
		
	}while(1);	
}
