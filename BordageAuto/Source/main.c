#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Servo.h"

//Pour l'instant j'ai pris comme base girouette et rajouter la partis servo en commentaire

#define TIMER_GIROUETTE TIM3
#define GIROUETTE_ARR 0x5A0 //360*4=1440


#define TIMER_PWM  //On doit choisir un timer différent de celui utilisé pour la girouette 
#define PWM_ARR 59999  // Valeurs choisis pour maximiser la précision 
#define PWM_PSC 24


//declaration de nos tymer girouette(GRT) et PWM

MyTimer_Struct_TypeDef MyTimer_GRT; 
//MyTimer_Struct_TypeDef MyTimer_PWM;

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

	PWM_Port_Init(3, 3);
	
	
	MyTimer_PWM(MyTimer_GRT.Timer, 3);
	
	//RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	//MyTimer_PWM.Timer = TIM3;
	//MyTimer_PWM.ARR = PWM_ARR;
	//MyTimer_PWM.PSC = PWM_PSC;
	//MyTimer_PWM.Timer_num = 3;
	
	//MyTimer_Base_Init(&MyTimer_PWM);
	//MyTimer_Base_Start(&MyTimer_PWM);
	//PWM_Port_Init(3, 3);
	
	
	//MyTimer_PWM(MyTimer_PWM.Timer, 3);
	
	//PWM_RapportCyclique(MyTimer.Timer, 3600); // ARR pour obtenir 90°
	//PWM_RapportCyclique(MyTimer.Timer, 4500);
	//PWM_RapportCyclique(MyTimer.Timer, 6400);	// ARR pour obtenir 0°
	
	do{
		angle_servo(MyTimer_GRT.Timer->CCR3, MyTimer_GRT.Timer);
	}while(1);	
}
