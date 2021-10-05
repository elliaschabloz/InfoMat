#include "stm32f10x.h"
#include "MyTimer.h"

static void( *tim2_function) (void);
static void( *tim3_function) (void);
static void( *tim4_function) (void);

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

void MyTimer_ActiveIT ( MyTimer_Struct_TypeDef * Timer, char Prio, void(*IT_function) (void)){
	uint16_t IRQn_Timer = 26+Timer->Timer_num;
	/* On met le UIE à 1 */
	NVIC->ISER[0] |= (1 << IRQn_Timer);
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
		default:
			break;
	}
	Timer->Timer->DIER |= (1<<0);
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
 
void MyTimer_PWM(TIM_TypeDef * Timer, char Channel){
	//Mode 1 -> OCxM bit = 110 in CCMRx
	switch (Channel) {
		case 1:
			Timer->CCMR1 = TIM_CCMR1_OC1M_2;
			Timer->CCMR1 = TIM_CCMR1_OC1M_1;
			Timer->CCMR1 = ~TIM_CCMR1_OC1M_0;
			
			Timer->CCER = TIM_CCER_CC1E;
			break;
		case 2:
			Timer->CCMR1 = TIM_CCMR1_OC2M_2;
			Timer->CCMR1 = TIM_CCMR1_OC2M_1;
			Timer->CCMR1 = ~TIM_CCMR1_OC2M_0;
			
			Timer->CCER = TIM_CCER_CC1E;
			break;
		case 3:
			Timer->CCMR1 = TIM_CCMR1_OC1M_2;
			Timer->CCMR1 = TIM_CCMR1_OC1M_1;
			Timer->CCMR1 = ~TIM_CCMR1_OC1M_0;
			
			Timer->CCER = TIM_CCER_CC1E;
			break;
		default:
			break;
	}
}

