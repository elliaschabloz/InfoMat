#include "stm32f10x.h"
#include "MyTimer.h"

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * MyTimer)
{	
	RCC->APB1RSTR |= (1<< (MyTimer->Timer_num -2));  // reset du timer
}

void MyTimer_Base_Start(MyTimer_Struct_TypeDef * MyTimer)
	{
		RCC->APB1ENR |= (1<<(MyTimer->Timer_num -2));		//enable du tim
		//On initialise les registre ARR et PSC selon nos paramètres
		//Et on active le clock register 
		MyTimer->Timer->CR1=0x01;
		MyTimer->Timer->ARR=MyTimer->ARR;
		MyTimer->Timer->PSC=MyTimer->PSC;
	}

void MyTimer_Base_Stop(MyTimer_Struct_TypeDef * Timer)
	{
		RCC->APB1ENR &= ~(1<<(Timer->Timer_num -2)); //disable du tim
}
