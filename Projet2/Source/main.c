#include "stm32f10x.h"
#include "MyTimer.h"

//on doit configurer le TIMER2 de période T = 500ms
//pour cela, on doit trouver les valeurs de PSC et ARR

// T_Timer = T_Horloge * (PSC+1)*(ARR+1)
// (ARR+1) = T_Timer / (T_Horloge * (PSC+1))
// 1/72 000 000 s = 1E-3 / 72000000*1E-3 s = 1 / 72000*1E-3 ms
// Pour PSC=2 => ARR+1 = 12 000 000 => ARR=11 999 999

#define PERIODE_TIM2 500
#define TIMER TIM2
#define PERIODE_CLK (1/72000)
#define TIMER_PSC 1000
#define TIMER_ARR 36000


static MyTimer_Struct_TypeDef MyTimer ;


int main(void) {
	
	
	/*On initialise le timer ? 0 cette formule est vraie pour les timer 2 ? 7*/
	RCC->APB1ENR |= (1<< 0);/*Le nombre de d?calage ccorrespond aux num de TIM -2*/

	MyTimer.Timer = TIM4;
	MyTimer_Base_Init(&MyTimer);

	do{
	
	}while(1);
		
}
