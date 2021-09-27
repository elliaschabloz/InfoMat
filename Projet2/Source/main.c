#include "stm32f10x.h"
#include "MyTimer.h"

//on doit configurer le TIMER2 de période T_Timer = 500ms
//pour cela, on doit trouver les valeurs de PSC et ARR

// T_Timer = T_Horloge * (PSC+1)*(ARR+1)
// (ARR+1) = T_Timer / (T_Horloge * (PSC+1))

// T_Horloge = 1/72 000 000 s = 1E-3 / (72 000 000*1E-3) s = 1 / 72 000  ms
// T_Timer/T_Horloge = (PSC+1)*(ARR+1)
// T_Timer/T_Horloge = 36 000 000
// On fixe PSC et ARR tel que (PSC+1)*(ARR+1)= 36 000 000
// Pour (PSC+1) =4000 =>3999 et (ARR+1= 9000)=> ARR=8999 

// Pour les variables PSC et ARR pensez à entrer les valeur en HEX dans le define

#define PERIODE_TIM2 500
#define MON_TIMER TIM2
#define PERIODE_CLK (1/72000) //On le déclare mais je sais pas quand on l'utilise mdr
#define TIMER_PSC 0x0F99 //3999
#define TIMER_ARR 0x2327 //8999


MyTimer_Struct_TypeDef MyTimer;


int main(void) {
	
	/*TEST en simulé pour mettre le clock a 0.5ms*/
	/*
	TIM2->CR1=0x01;
	TIM2->ARR=0x2327;
	TIM2->PSC=0x0F99;
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
