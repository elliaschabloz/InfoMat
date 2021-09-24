#include "stm32f10x.h"
#include "MyTimer.h"

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * Timer)
{	
	RCC->APB1RSTR |= (1<< (Timer->Timer_num -2));  // reset du timer
}

void MyTimer_Base_Start(MyTimer_Struct_TypeDef * Timer)
	{
		RCC->APB1ENR |= (1<<(Timer->Timer_num -2)); //enable du tim
}

void MyTimer_Base_Stop(MyTimer_Struct_TypeDef * Timer)
	{
		RCC->APB1ENR &= ~(1<<(Timer->Timer_num -2)); //disable du tim
}
