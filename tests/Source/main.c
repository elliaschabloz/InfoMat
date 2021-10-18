#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

#define MON_TIMER TIM3
#define TIMER_ARR 0x5A0 //360*4=1440

MyTimer_Struct_TypeDef MyTimer;
void Callback(void){
}

void Init_CODER(void){ //Zero
	
	MyGPIO_Struct_TypeDef CODER;
	CODER.GPIO = GPIOA;
	CODER.GPIO_Pin = 0;	
	CODER.GPIO_Conf =	In_PullUp;
	MyGPIO_Init(&CODER);
}

void Init_CHA(void){ //TIM3_CH1=PA6
	MyGPIO_Struct_TypeDef CHA;
	CHA.GPIO = GPIOA;
	CHA.GPIO_Pin = 6;	
	CHA.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&CHA);
}

void Init_CHB(void){ //TIM3_CH2=PA7
	MyGPIO_Struct_TypeDef CHB;
	CHB.GPIO = GPIOA;
	CHB.GPIO_Pin = 7;	
	CHB.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&CHB);
}

int main(void) {
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; //Clock Enable
	
	MyTimer.Timer = MON_TIMER;
	MyTimer.ARR = TIMER_ARR;
	MyTimer.Timer_num = 3;
	MyTimer_Base_Init(&MyTimer);
	MyTimer_Base_Start(&MyTimer);
	
	Init_CHA();
  Init_CHB();
	Init_CODER();
	
	MyTimer_Encoder_Init(MON_TIMER);
	MyZero_ActiveIT(5);
	
	// Quand on met les fonctions init et start le registre CNT se met pas à jour
	// Je pense qu'ils sont contradictoir je lis la doc puis je verrais une soluce
	
	//MyTimer_Base_Start(&MyTimer);
	//MyTimer_PWM(TIM_TypeDef * Timer, char Channel)
	//MyTimer_ActiveIT(&MyTimer, 5, &Callback);
	do{
	
	}while(1);	
}
