/*
 * main.c
 *
 * Created: 11/7/2019 8:10:43 PM
 *  Author: Hamdy
 */ 


#include "ExternalInterrupts_ATmega32A.h"
//#include "GameSW.h"
#include "LED.h"
#include "DIO_ATmega32A.h"
#include <util/delay.h>
   uint8_t i;
   #include "EEPROM.h"
   #include "EEPROMTEST.h"
   
    ledDatatype LED0={DIOD,PIN0};
    ledDatatype LED1={DIOD,PIN1};
    ledDatatype LED2={DIOD,PIN4};
    ledDatatype LED3={DIOD,PIN5};
    ledDatatype LED4={DIOB,PIN0};
    ledDatatype LED5={DIOB,PIN1};
    ledDatatype LED6={DIOB,PIN2};
    ledDatatype LED7={DIOB,PIN3};
	ledDatatype *LEDS[8]={&LED0,&LED1,&LED2,&LED3,&LED4,&LED5,&LED6,&LED7};
		
		
int main()
{
	EEPROM_WRITE(1,5);
	//ExternalInterrupt_Configure(EXTINT0,EXTINT_RISING);
	//AlertButtonInterrupt_Init();
	//		setup();
	//	 FirstSW ();
	//	 SecondSWitch ();
	//	 ThirdSWitch ();
	LEDSBUTTON();
			 LEDSetup(LED0);
			 LEDSetup(LED1);
			 LEDSetup(LED2);
			 LEDSetup(LED3);
			 LEDSetup(LED4);
			 LEDSetup(LED5);
			 LEDSetup(LED6);
			 LEDSetup(LED7);
			 LEDSBUTTON();
	if( EEPROM_READ(0) == 0xFF)
	{
		i=0;
		EEPROM_WRITE(0,i);
		_delay_ms(1);
	}
	i = EEPROM_READ(0);
	_delay_ms(1);
	uint8_t j=0;
	

	while(1)
	{
		/*if (i >= 7)
		{
			uint8_t FULL = 0b11111111;
			uint8_t EMPTY = 0;
			DIO_portWrite(DIOA,FULL);
			_delay_ms(300);
			DIO_portWrite(DIOA,EMPTY);
			_delay_ms(300);
		}
		 if (j >= 7)
		{
						uint8_t FULL = 0b11111111;
						uint8_t EMPTY = 0;
						DIO_portWrite(DIOC,FULL);
						_delay_ms(300);
						DIO_portWrite(DIOC,EMPTY);
						_delay_ms(300);
		}
	}	*/
		for(j=0;j<=i;j++)
		{
			LEDControl(*LEDS[j],LED_ON);
		}
	}
}
