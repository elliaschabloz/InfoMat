
#include "stm32f10x.h"

//on doit configurer le TIMER2 de période T = 500ms
//pour cela, on doit trouver les valeurs de PSC et ARR

// T_Timer = T_Horloge * (PSC+1)*(ARR+1)
// (ARR+1) = T_Timer / (T_Horloge * (PSC+1))
// 1/72 000 000 s = 1E-3 / 72000000*1E-3 s = 1 / 72000*1E-3 ms
// Pour PSC=2 => ARR+1 = 12 000 000 => ARR=11 999 999

#define PERIODE_TIM2 500
#define TIMER TIM2
#define PERIODE_CLK = (1/72000)
#define PSC 2
#define ARR 11999999




int main(void) {
	
	
	/*On initialise le timer ? 0 cette formule est vraie pour les timer 2 ? 7*/
	RCC->APB1ENR |= (1<< 0);/*Le nombre de d?calage ccorrespond aux num de TIM -2*/

	TIMER->PSC |= (1<< 2);
	TIMER->ARR = 11999999; /**/

	do{}while(1);
	
	
	
	return 0;
}
