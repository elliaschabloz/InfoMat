#include "stm32f10x.h"
#include "Driver_GPIO.h"

#define BROCHE_LED (0)
#define BROCHE_BTN_BLUE (1)
#define GPIO_BTN GPIOC
#define GPIO_LED GPIOB
#define OUT_PP_2MHZ 0x2


MyGPIO_Struct_TypeDef LED;
MyGPIO_Struct_TypeDef BTN;
	
int main(void)
{
	
	// Init
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
		
	//Config LED en output push/pull
	
	LED.GPIO = GPIO_LED;
	LED.GPIO_Pin = BROCHE_LED;	
	LED.GPIO_Conf =	Out_Ppull;
	MyGPIO_Init(&LED);
	
	// Config BTN en floating input	

	BTN.GPIO = GPIO_BTN;
	BTN.GPIO_Pin = BROCHE_BTN_BLUE;	
	BTN.GPIO_Conf =	In_Floating;
	MyGPIO_Init(&BTN);
	
	// Si le BTN est appuyé, la led s'allume
	do
	{	
		//MyGPIO_Set(BTN.GPIO, 13); //appuie sur le bouton
		//MyGPIO_Reset(BTN.GPIO, 13); //lache le bouton
		
		if( (MyGPIO_Read(BTN.GPIO,BTN.GPIO_Pin)) != 0x0){
			MyGPIO_Set(LED.GPIO, LED.GPIO_Pin); //appuie sur le bouton
		}else{
			MyGPIO_Reset(LED.GPIO, LED.GPIO_Pin); //lache le bouton
		};
	}
	while(1) ;
	
}
