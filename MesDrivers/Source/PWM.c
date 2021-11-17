#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


short TIMER1_TAB_CH[4] = {8,9,10,11}; // GPIOA
short TIMER2_TAB_CH[4] = {0,1,2,3};		//GPIOA
short TIMER3_TAB_CH[4] = {6,7,0,1};		// GPIOA puis GPIOB
short TIMER4_TAB_CH[4] = {6,7,8,9};		//GPIOB

//On initialise le port associé aux channel choisi
void PWM_Port_Init(int Timer_number, int Channel){
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
			PWM_Output.GPIO_Pin = TIMER2_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;
		case 3:
			if(Channel<=2){
				PWM_Output.GPIO = GPIOA;
			}else{
				PWM_Output.GPIO = GPIOB;
			}
			PWM_Output.GPIO_Pin = TIMER3_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;
		case 4:
			PWM_Output.GPIO = GPIOB;
			PWM_Output.GPIO_Pin = TIMER4_TAB_CH[Channel-1] ;	
			PWM_Output.GPIO_Conf =	AltOut_Ppull;
			MyGPIO_Init(&PWM_Output);
			break;		
	}
}
 
void PWM_RapportCyclique(TIM_TypeDef * Timer, int alpha){
	Timer->CCR2 = alpha;	
}

void MyTimer_PWM(TIM_TypeDef * Timer, int Channel){
	//Mode 1 -> OCxM bit = 110 in CCMRx
	switch (Channel) {
		case 1:
			Timer->CCMR1 |= TIM_CCMR1_OC1M_2;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_1;
			//Timer->CCMR1 |= ~TIM_CCMR1_OC1M_0;
			
			Timer->CCER |= TIM_CCER_CC1E;
			break;
		case 2:
			Timer->CCMR1 |= TIM_CCMR1_OC2M_2;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_1;
			//Timer->CCMR1 |= ~TIM_CCMR1_OC2M_0;
			
			Timer->CCER |= TIM_CCER_CC2E;
			break;
		case 3:
			Timer->CCMR2 |= TIM_CCMR2_OC3M_2;
			Timer->CCMR2 |= TIM_CCMR2_OC3M_1;
			//Timer->CCMR2 |= ~TIM_CCMR2_OC3M_0;
			
			Timer->CCER |= TIM_CCER_CC3E;
			break;
		case 4:
			Timer->CCMR2 |= TIM_CCMR2_OC4M_2;
			Timer->CCMR2 |= TIM_CCMR2_OC4M_1;
			//Timer->CCMR2 |= ~TIM_CCMR2_OC4M_0;
			
			Timer->CCER |= TIM_CCER_CC4E;
			break;		
	}
}
