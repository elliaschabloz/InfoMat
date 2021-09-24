#include "stm32f10x.h"
#include "MyTimer.h"

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * Timer)
{	
	Timer->ARR = TIMER_ARR;
	Timer->PSC = TIMER_PSC;
}

void MyTimer_Base_Start(MyTimer_Struct_TypeDef * Timer){
	
}

void MyTimer_Base_Stop(MyTimer_Struct_TypeDef * Timer){
	
}
