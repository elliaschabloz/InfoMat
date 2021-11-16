#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct{
	TIM_TypeDef * Timer; // TIM1 à TIM4
	unsigned short ARR;
	unsigned short PSC;
	char Timer_num;
}MyTimer_Struct_TypeDef;


/*
*****************************************************************************************
			*@brief
			*@param-> Paramètre sous forme d’une structure (son adresse) contenant les informations de base
			*@Note-> Fonction à lancer systématiquement avant d’aller plus en détail dans les conf plus  fines (PWM, codeur inc ...)
*************************************************************************************************
*/

void MyTimer_Base_Init (MyTimer_Struct_TypeDef *Timer) ;
void MyTimer_Base_Start(MyTimer_Struct_TypeDef *Timer);
void MyTimer_Base_Stop(MyTimer_Struct_TypeDef *Timer);

/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/
void MyTimer_ActiveIT ( MyTimer_Struct_TypeDef * Timer , char Prio, void(*IT_function) (void));
void TIM2_IRQHandler ( void );
void TIM3_IRQHandler ( void );
void TIM4_IRQHandler ( void );

#endif
