#include "stm32f10x.h"
#include "MyTimer.h"

//on doit configurer le TIMER2 de période T = 500ms
//pour cela, on doit trouver les valeurs de PSC et ARR

// T_Timer = T_Horloge * (PSC+1)*(ARR+1)
// (ARR+1) = T_Timer / (T_Horloge * (PSC+1))
// 1/72 000 000 s = 1E-3 / 72000000*1E-3 s = 1 / 72000*1E-3 ms
// Pour PSC=2 => ARR+1 = 12 000 000 => ARR=11 999 999

#define PERIODE_TIM2 500
#define MON_TIMER TIM2
#define PERIODE_CLK (1/72000)
#define TIMER_PSC 1000
#define TIMER_ARR 36000


 MyTimer_Struct_TypeDef MyTimer;


int main(void) {
<<<<<<< HEAD
		
	MyTimer.Timer = MON_TIMER;
=======
	
	
	/*On initialise le timer ? 0 cette formule est vraie pour les timer 2 ? 7*/
	RCC->APB1ENR |= (1<< 0);/*Le nombre de d?calage ccorrespond aux num de TIM -2*/
	
	/*TEST en simulé pour mettre le clock a 0.5ms*/
	/*
	TIM2->CR1=0x01;
	TIM2->ARR=0x2450;
	TIM2->PSC=0x1770;
	*/
	
	MyTimer.Timer = TIMER;
>>>>>>> 9173126c475d27b3679b460546051275d2d1b8aa
	MyTimer.ARR = TIMER_ARR;
	MyTimer.PSC = TIMER_PSC;
	MyTimer.Timer_num = 2;
	
	MyTimer_Base_Init(&MyTimer);

	do{
	
	}while(1);
		
}
