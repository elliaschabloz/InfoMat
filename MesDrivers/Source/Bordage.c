#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Servo.h"
#include "PWM.h"
#include "Encoder.h"

#define TIMER_GIROUETTE TIM3
#define GIROUETTE_ARR 0x5A0 //360*4=1440

#define TIMER_PWM TIM2 
#define PWM_ARR 59999
#define PWM_PSC 24

void bordage_auto(void){
	angle_servo(TIMER_GIROUETTE->CNT/4, TIMER_PWM);
}

void init_bordage(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN ; // Broches girouettes sur GPIOA & GPIOB
	
	//declaration de nos tymer girouette GRT et PWM
	MyTimer_Struct_TypeDef MyTimer_GRT; 
	MyTimer_Struct_TypeDef MyTimerPWM;

	//GIROUETTE
	MyTimer_GRT.Timer = TIMER_GIROUETTE;
	MyTimer_GRT.ARR = GIROUETTE_ARR;
	MyTimer_GRT.Timer_num = 3;
	MyTimer_Base_Init(&MyTimer_GRT);
	MyTimer_Base_Start(&MyTimer_GRT);

	//TIM3_CH1=PA6
	//GPIOA6
	MyGPIO_Struct_TypeDef CHA;
	CHA.GPIO = GPIOA;
	CHA.GPIO_Pin = 6;	
	CHA.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&CHA);

  //TIM3_CH2=PA7
	//GPIOA7
	MyGPIO_Struct_TypeDef CHB;
	CHB.GPIO = GPIOA;
	CHB.GPIO_Pin = 7;	
	CHB.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&CHB);
	
	//Zero
	//GPIOA0
	MyGPIO_Struct_TypeDef ZERO;
	ZERO.GPIO = GPIOA;
	ZERO.GPIO_Pin = 0;	
	ZERO.GPIO_Conf =	In_PullUp;
	MyGPIO_Init(&ZERO);
	
	//ENCODER
	MyTimer_Encoder_Init(TIMER_GIROUETTE);
	MyZero_ActiveIT(5);
	
	//SERVO PWM
	MyTimerPWM.Timer = TIMER_PWM;
	MyTimerPWM.ARR = PWM_ARR;
	MyTimerPWM.PSC = PWM_PSC;
	MyTimerPWM.Timer_num = 2;
	MyTimer_Base_Init(&MyTimerPWM);
	MyTimer_Base_Start(&MyTimerPWM);
	PWM_Port_Init(2, 2);
	MyTimer_PWM(MyTimerPWM.Timer, 2);
	
	MyTimer_ActiveIT (&MyTimerPWM, 5, &bordage_auto);

}

