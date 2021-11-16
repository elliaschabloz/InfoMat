#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


static void( *tim2_function) (void);
static void( *tim3_function) (void);
static void( *tim4_function) (void);

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * MyTimer)
{	
	RCC->APB1ENR |= (1<<(MyTimer->Timer_num -2));		//enable du tim
	MyTimer->Timer->ARR=MyTimer->ARR;
	MyTimer->Timer->PSC=MyTimer->PSC;
}

void MyTimer_Base_Start(MyTimer_Struct_TypeDef * MyTimer)
	{
		//On active le clock register 
		MyTimer->Timer->CR1 |= TIM_CR1_CEN;		
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

void MyTimer_ActiveIT ( MyTimer_Struct_TypeDef * Timer, char Prio, void(*IT_function) (void)){
	uint16_t IRQn_Timer = 26+Timer->Timer_num;
	NVIC->ISER[0] |= (1 << IRQn_Timer); //activation IT NVIC
	NVIC_SetPriority((IRQn_Type)IRQn_Timer,Prio);
	IT_function();
	switch (Timer->Timer_num){
		case 2:
			tim2_function = IT_function;
			break;
		case 3:
			tim3_function = IT_function;
			break;
		case 4:
			tim4_function = IT_function;
			break;
	}
	Timer->Timer->DIER |= TIM_DIER_UIE; //activation IT NVIC
}


void TIM2_IRQHandler ( void )
{
	TIM2->SR &= ~TIM_SR_UIF;
	tim2_function();
	
	
}

void TIM3_IRQHandler ( void )
{
	TIM3->SR &= ~TIM_SR_UIF;
	tim3_function();
}

void TIM4_IRQHandler ( void )
{
	TIM4->SR &= ~TIM_SR_UIF;
	tim4_function();
}
