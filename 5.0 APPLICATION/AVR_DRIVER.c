/*
 * AVR_DRIVER.c
 *
 * Created: 6/9/2020 2:50:14 PM
 *  Author: 8
 */ 
 #include "LED.h"
 #include "KEYPAD.h"
 #include "LCD.h"
 #include "util/delay.h"
 #include "RELAY.h"


	
int main(void)
{
	
	RelaySetup();
    while(1)
    {
		RelayControl(HIGH);
		_delay_ms(5000);
		RelayControl(HIGH);
		_delay_ms(5000);
			
						
	}

}
