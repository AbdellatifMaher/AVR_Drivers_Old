/*
 * KEYPADWITHLED.c
 *
 * Created: 8/19/2020 6:52:02 PM
 *  Author: 8
 */ 
/*
 * AVR_DRIVER.c
 *
 * Created: 6/9/2020 2:50:14 PM
 *  Author: 8
 */ 
/* #include "LED.h"
 #include "KEYPAD.h"
 
 ledDatatype WLED={DIOA,PIN0};
 ledDatatype RLED={DIOA,PIN1};
 ledDatatype YLED={DIOA,PIN2};
ledDatatype  BLED={DIOA,PIN3};
 

int main(void)
{
	LEDSetup(WLED);
	LEDControl(WLED,LED_OFF);
	LEDSetup(RLED);
	LEDControl(BLED,LED_OFF);
	LEDSetup(BLED);
	LEDControl(WLED,LED_OFF);
	LEDSetup(YLED);
	LEDControl(RLED,LED_OFF);
	Key_Configure(DIOC);

    while(1)
    {
		uint8_t ch=Key_PRESSED(DIOC);
		if(ch)
		{
			switch(ch)
			{
				case '1' : LEDControl(WLED,LED_ON);break;
				case '4' : LEDControl(RLED,LED_ON);break;
				case '7' : LEDControl(YLED,LED_ON);break;
				case 'A' : LEDControl(BLED,LED_ON);break;
				case 'B' : LEDControl(WLED,LED_OFF);break;
				case '0' : LEDControl(RLED,LED_OFF);break;
				case '*' : LEDControl(BLED,LED_OFF);break;
				case '#' : LEDControl(YLED,LED_OFF);break;
			}
		}
	       //TODO:: Please write your application code 
    }
} */