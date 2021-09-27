#include "stm32f10x.h"
#include "MyTimer.h"

//on doit configurer le TIMER2 de période T_Timer = 500ms
//pour cela, on doit trouver les valeurs de PSC et ARR

// T_Timer = T_Horloge * (PSC+1)*(ARR+1)
// (ARR+1) = T_Timer / (T_Horloge * (PSC+1))

// T_Horloge = 1/72 000 000 s = 1E-3 / (72 000 000*1E-3) s = 1 / 72 000  ms
// 500ms de période -> f=2Hz
// PSC*ARR = 72M/2 = 36M
//PSC = Partie entière supp( 36/2**16) ARR=Q(36/PSC)
// PSC=1099 ARR=

// Pour les variables PSC et ARR pensez à entrer les valeur en HEX dans le define

#define PERIODE_TIM2 500
#define MON_TIMER TIM2
#define PERIODE_CLK (1/72000) //On le déclare mais je sais pas quand on l'utilise mdr
#define TIMER_ARR 0xFFAE //65454
#define TIMER_PSC 0x0225 //550


MyTimer_Struct_TypeDef MyTimer;


int main(void) {
	
	/*TEST en simulé pour mettre le clock a 0.5ms*/
	/*
	TIM2->CR1=0x01;
	TIM2->ARR=0xFFAE; // 65454
	TIM2->PSC=0x0226; // 550
	// Choix d'ARR pour une précision accrues
	*/
	
	MyTimer.Timer = MON_TIMER;
	MyTimer.ARR = TIMER_ARR;
	MyTimer.PSC = TIMER_PSC;
	MyTimer.Timer_num = 2;
	
	//MyTimer_Base_Init(&MyTimer);
	// Quand on met les fonctions init et start le registre CNT se met pas à jour
	// Je pense qu'ils sont contradictoir je lis la doc puis je verrais une soluce
	
	MyTimer_Base_Start(&MyTimer);

	do{
	}while(1);	
}
