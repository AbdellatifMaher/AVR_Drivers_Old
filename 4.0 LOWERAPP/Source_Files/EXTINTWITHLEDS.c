/*
 * EXTINTWITHLEDS.c
 *
 * Created: 8/15/2020 11:23:57 PM
 *  Author: 8
 */ 
/*#include "LED.h"
#include "EXT_Interrupt.h"
#include "PushButton.h"
#include "GPIO_ATmega32A.h"

ledDatatype WLED={DIOA,PIN0};
ledDatatype RLED={DIOA,PIN7};
PushButton_datatype PB={DIOC,PIN0};
void fun(void)
{
	LEDControl(WLED,LED_TOGGLE);
}


int main(void)
{
	DIO_pinConfigure(DIOD,PIN2,INPUT_PULLUP);
	LEDSetup(WLED);
	LEDControl(WLED,LED_ON);
	LEDSetup(RLED);
	LEDControl(RLED,LED_OFF);
	PushButton_Setup(PB);
	GLOBAL_INTERRUPT_ENABLE();
	ExternalInterrupt_Configure(EXTINT0,EXTINT_FALLING);
	EXTINT0_Functionp=fun;
	

	while(1)
	{
		if(PushButton_Read(PB) == HIGH)
		{
			LEDControl(RLED,LED_ON);
		}
		else
		{
			LEDControl(RLED,LED_OFF);
		}     //TODO:: Please write your application code
	}
} */