#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Servo.h"

//Pour l'instant j'ai pris comme base girouette et rajouter la partis servo en commentaire

#define TIMER_GIROUETTE TIM3
#define GIROUETTE_ARR 0x5A0 //360*4=1440


#define TIMER_PWM TIM4 //On doit choisir un timer différent de celui utilisé pour la girouette 
#define PWM_ARR 59999  // Valeurs choisis pour maximiser la précision 
#define PWM_PSC 24


//declaration de nos tymer girouette(GRT) et PWM

MyTimer_Struct_TypeDef MyTimer_GRT; 
MyTimer_Struct_TypeDef MyTimerPWM;

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
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN ; // Broches girouettes sur GPIOA & GPIOB
	//RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
	MyTimer_GRT.Timer = TIMER_GIROUETTE;
	MyTimer_GRT.ARR = GIROUETTE_ARR;
	MyTimer_GRT.Timer_num = 3;
	MyTimer_Base_Init(&MyTimer_GRT);
	MyTimer_Base_Start(&MyTimer_GRT);
	
	Init_CHA();
  Init_CHB();
	Init_CODER();
	
	MyTimer_Encoder_Init(TIMER_GIROUETTE);
	MyZero_ActiveIT(5);

	
	MyTimerPWM.Timer = TIM4;
	MyTimerPWM.ARR = PWM_ARR;
	MyTimerPWM.PSC = PWM_PSC;
	MyTimerPWM.Timer_num = 4;
	
	MyTimer_Base_Init(&MyTimerPWM);
	MyTimer_Base_Start(&MyTimerPWM);
	
	PWM_Port_Init(4, 1);
	
	
	MyTimer_PWM(MyTimerPWM.Timer, 1);
	
	
	do{
		//PWM_RapportCyclique(MyTimerPWM.Timer, 3000);
		//angle_servo(316, MyTimerPWM.Timer);
		angle_servo(MyTimer_GRT.Timer->CNT/4, MyTimerPWM.Timer);
	}while(1);	
}
