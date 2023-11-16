/*
 * LED.c
 *
 * Created: 6/10/2020 12:17:26 AM
 *  Author: Abdellatif
 */ 

	#include "LED.h"
	#include "GPIO_ATmega32A.h"
	
	
	void LEDSetup(ledDatatype led)
	{
		DIO_pinConfigure(led.LED_Dio,led.LED_pin,OUTPUT);
	}
	
	void LEDControl(ledDatatype led, LEDstate state)
	{
		switch(state)
		{
			// LED_OFF is the same as LED_ON_REVERSED
			case LED_OFF:
			DIO_pinWrite(led.LED_Dio,led.LED_pin,LOW);
			break;
			case LED_ON:
			DIO_pinWrite(led.LED_Dio,led.LED_pin,HIGH);
			break;
			case LED_TOGGLE:
			DIO_pinWrite(led.LED_Dio,led.LED_pin,!DIO_pinRead(led.LED_Dio,led.LED_pin));
			break;
			default:  break;
		}
	}