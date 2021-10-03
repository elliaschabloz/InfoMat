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
	
/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/

void MyTimer_ActiveIT ( MyTimer_Struct_TypeDef * Timer, char Prio){
	uint16_t IRQn_Timer = 26+Timer->Timer_num;
	/* On met le UIE à 1 */
	NVIC->ISER[0] |= (1 << IRQn_Timer);
	NVIC_SetPriority((IRQn_Type)IRQn_Timer,Prio);
	Timer->Timer->DIER |= (1<<0);
}


void TIM2_IRQHandler ( void )
{
	TIM2->DIER &= ~(1<<0);
}

void TIM3_IRQHandler ( void )
{
	TIM3->DIER &= ~(1<<0); 
	
}

void TIM4_IRQHandler ( void )
{
	TIM4->DIER &= ~(1<<0);
	
}
 
