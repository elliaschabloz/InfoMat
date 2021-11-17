/*
Bordage.h
-----
*/
#ifndef BORDAGE_H
#define BORDAGE_H
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Servo.h"
#include "PWM.h"
#include "Encoder.h"

void init_bordage(void);
void bordage_auto(void);


#endif
