#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Servo.h"

#define TIMER_GIROUETTE TIM3
#define GIROUETTE_ARR 0x5A0 //360*4=1440


#define TIMER_PWM TIM4 
#define PWM_ARR 59999
#define PWM_PSC 24


//declaration de nos tymer girouette GRT et PWM
MyTimer_Struct_TypeDef MyTimer_GRT; 
MyTimer_Struct_TypeDef MyTimerPWM;

//////////////////////////////
//Fonctions d'initialisation//
//////////////////////////////
void Init_ZERO(void){ //Zero
	//GPIOA0
	MyGPIO_Struct_TypeDef ZERO;
	ZERO.GPIO = GPIOA;
	ZERO.GPIO_Pin = 0;	
	ZERO.GPIO_Conf =	In_PullUp;
	MyGPIO_Init(&ZERO);
}

void Init_CHA(void){ //TIM3_CH1=PA6
	//GPIOA6
	MyGPIO_Struct_TypeDef CHA;
	CHA.GPIO = GPIOA;
	CHA.GPIO_Pin = 6;	
	CHA.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&CHA);
}

void Init_CHB(void){ //TIM3_CH2=PA7
	//GPIOA7
	MyGPIO_Struct_TypeDef CHB;
	CHB.GPIO = GPIOA;
	CHB.GPIO_Pin = 7;	
	CHB.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&CHB);
}

void Init_GRT(void){
	MyTimer_GRT.Timer = TIMER_GIROUETTE;
	MyTimer_GRT.ARR = GIROUETTE_ARR;
	MyTimer_GRT.Timer_num = 3;
	MyTimer_Base_Init(&MyTimer_GRT);
	MyTimer_Base_Start(&MyTimer_GRT);
}

void Init_PWM(void){
	MyTimerPWM.Timer = TIM4;
	MyTimerPWM.ARR = PWM_ARR;
	MyTimerPWM.PSC = PWM_PSC;
	MyTimerPWM.Timer_num = 4;
	MyTimer_Base_Init(&MyTimerPWM);
	MyTimer_Base_Start(&MyTimerPWM);
	PWM_Port_Init(4, 1);
	MyTimer_PWM(MyTimerPWM.Timer, 1);
}

int main(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN ; // Broches girouettes sur GPIOA & GPIOB
	//RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
	
	Init_GRT();
	Init_CHA();
  Init_CHB();
	Init_ZERO();
	
	MyTimer_Encoder_Init(TIMER_GIROUETTE);
	MyZero_ActiveIT(5);

	Init_PWM();	
	
	do{
		//PWM_RapportCyclique(MyTimerPWM.Timer, 3000);
		//angle_servo(316, MyTimerPWM.Timer);
		angle_servo(MyTimer_GRT.Timer->CNT/4, MyTimerPWM.Timer);
	}while(1);	
}
