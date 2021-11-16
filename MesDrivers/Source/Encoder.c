#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


void MyTimer_Encoder_Init(TIM_TypeDef * Timer){
	Timer->CCMR1 |= TIM_CCMR1_CC1S_0; //CC1S=01 -> IC1 mapped on TI1
	Timer->CCMR1 |= TIM_CCMR1_CC2S_1; //CC2S=10 -> IC2 mapped on TI2
	//Mode 3 du codeur : SMCR_SMS = 011
	Timer->SMCR |= (TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1);
}

void MyZero_ActiveIT(char Prio){
	//pin=PA0 -> EXTI0
	EXTI->IMR = EXTI_IMR_MR0; 
	EXTI->RTSR = EXTI_RTSR_TR0;
	EXTI->FTSR = EXTI_FTSR_TR0;
	//NVIC_SetPendingIRQ(EXTI0_IRQn);
	NVIC->ISER[0] |= (1 << EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn,Prio);
}

void EXTI0_IRQHandler (void)
{
	TIM3->CNT &= 0;
	EXTI->PR |= EXTI_PR_PR0;
}
