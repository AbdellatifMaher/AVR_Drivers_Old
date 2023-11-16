/*
 * LED.h
 *
 * Created: 6/10/2020 12:14:07 AM
 *  Author: Abdellatif
 */ 


#ifndef LED_H_
#define LED_H_

  #include "GPIO_ATmega32A.h"
  #include "uc_Configuration.h"
  
  
typedef enum
				{
					LED_OFF=0,
					LED_OFF_REVERSED=1,
					LED_ON=1,
					LED_ON_REVERSED=0,
					LED_TOGGLE=2,
				}LEDstate;

typedef struct
					{
						DIO * LED_Dio;
						pinNumber LED_pin;
					}ledDatatype;

void LEDSetup(ledDatatype led);
void LEDControl(ledDatatype led, LEDstate state);



#endif /* LED_H_ */