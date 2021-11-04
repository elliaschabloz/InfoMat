#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr) {
			//verifier si CRL ou CRH
			if((*GPIOStructPtr).GPIO_Pin <=7) { //si Pin<7 alors CRL sinon CRH
					(*GPIOStructPtr).GPIO->CRL &= ~(0xF << (*GPIOStructPtr).GPIO_Pin*4);
					(*GPIOStructPtr).GPIO->CRL |= ((*GPIOStructPtr).GPIO_Conf << (*GPIOStructPtr).GPIO_Pin*4);
			} else {
					(*GPIOStructPtr).GPIO->CRH &= ~(0xF << ((*GPIOStructPtr).GPIO_Pin - 8)*4);
					(*GPIOStructPtr).GPIO->CRH |= ((*GPIOStructPtr).GPIO_Conf << ((*GPIOStructPtr).GPIO_Pin - 8)*4);
			}			
};


int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
		return GPIO->IDR &(1<<GPIO_Pin);
}; // renvoie 0 ou autre chose different de 0

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
		//GPIO -> ODR |= (0x01 << GPIO_Pin);
		GPIO->BSRR |= (0x01 << GPIO_Pin);
};

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
		//GPIO -> ODR &= ~(0x01 << GPIO_Pin);
		GPIO->BSRR |= (0x01 << (16+GPIO_Pin));
} ;

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
		if (!(GPIO->ODR & (1<<GPIO_Pin))) { //si rien ne change, on avait un zero
			MyGPIO_Set(GPIO, GPIO_Pin);																 //donc on met un 1
		} else {MyGPIO_Reset(GPIO, GPIO_Pin);};														 // sinon on met un 0
};
