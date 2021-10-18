#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

short TIMER1_TAB_CH[4] = {8,9,10,11}; // GPIOA
short TIMER2_TAB_CH[4] = {0,1,2,3};		//GPIOA
short TIMER3_TAB_CH[4] = {6,7,0,1};		// GPIOA pui GPIOB
short TIMER4_TAB_CH[4] = {6,7,8,9};		//GPIOB


static void( *tim2_function) (void);
static void( *tim3_function) (void);
static void( *tim4_function) (void);

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * MyTimer)
{	
	RCC->APB1RSTR |= (1<< (MyTimer->Timer_num -2));  // reset du timer
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


void MyZero_ActiveIT(char Prio){
	//pin=PA0 -> EXTI0

	EXTI->IMR = EXTI_IMR_MR0; 
	EXTI->RTSR = EXTI_RTSR_TR0;
	EXTI->FTSR = EXTI_FTSR_TR0;
	NVIC_SetPendingIRQ(EXTI0_IRQn);
	NVIC->ISER[0] |= (1 << EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn,Prio);
	
	
}

void EXTI0_IRQHandler (void)
{
	TIM3->CNT &= 0;
	TIM3->SR &= ~TIM_SR_UIF;
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
	

//On initialise le port associé aux channel choisi
void PWM_Port_Init(int Timer_number, char Channel){
	MyGPIO_Struct_TypeDef PWM_Output;
	switch (Timer_number) {
		case 1:
			PWM_Output.GPIO = GPIOA;
			PWM_Output.GPIO_Pin = TIMER1_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;
		case 2:
			PWM_Output.GPIO = GPIOA;
			PWM_Output.GPIO_Pin = TIMER1_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;
		case 3:
			if(Channel<=2){
				PWM_Output.GPIO = GPIOA;
			}else{
				PWM_Output.GPIO = GPIOB;
			}
			PWM_Output.GPIO_Pin = TIMER1_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;
		case 4:
			PWM_Output.GPIO = GPIOB;
			PWM_Output.GPIO_Pin = TIMER1_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;		
	}
}
 
void PWM_RapportCyclique(TIM_TypeDef * Timer, int alpha){
	// A voir si Le C fait la multiplication int hex et return un hex 
	// printf("%d",alpha*Timer->ARR);
	
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
			
			Timer->CCER = TIM_CCER_CC2E;
			break;
		case 3:
			Timer->CCMR2 = TIM_CCMR2_OC3M_2;
			Timer->CCMR2 = TIM_CCMR2_OC3M_1;
			Timer->CCMR2 = ~TIM_CCMR2_OC3M_0;
			
			Timer->CCER = TIM_CCER_CC3E;
			break;
		case 4:
			Timer->CCMR2 = TIM_CCMR2_OC4M_2;
			Timer->CCMR2 = TIM_CCMR2_OC4M_1;
			Timer->CCMR2 = ~TIM_CCMR2_OC4M_0;
			
			Timer->CCER = TIM_CCER_CC4E;
			break;		
	}
}
	// Il est censé prendre en argument le tim mais soucis avec les type TIM à revoir

