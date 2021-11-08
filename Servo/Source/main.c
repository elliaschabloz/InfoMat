#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


MyTimer_Struct_TypeDef MyTimer;


void Callback(void){
}



int main(void) {
	
	PWM_Port_Init(2, 3);
	MyTimer_PWM(MyTimer.Timer, 3);
	
	PWM_RapportCyclique(MyTimer.Timer, 30);
	
	do{
		PWM_RapportCyclique(MyTimer.Timer, 30);
		PWM_RapportCyclique(MyTimer.Timer, 0);
	}while(1);	
}
