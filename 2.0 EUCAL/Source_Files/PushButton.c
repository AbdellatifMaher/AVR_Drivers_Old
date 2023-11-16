/*
 * PushButton.c
 *
 * Created: 8/11/2020 6:30:00 PM
 *  Author: 8
 */ 

#include "PushButton.h"

#define BUTTON_BOUNCE_PERIOD_mS	(60)

void ButtonSw_Setup(ButtonSw_datatype * Button)
{
	switch(Button->InputMode)
	{
		case INPUT_FLOAT:
		DIO_pinConfigure(Button->Button_Dio,Button->Button_Pin,INPUT_FLOAT);
		break;
		case INPUT_PULLUP:
		DIO_pinConfigure(Button->Button_Dio,Button->Button_Pin,INPUT_PULLUP);
		break;
		default:
		Button_UserWarningError();
		break;
	}
	Button->PrevButton_State = DIO_pinRead(Button->Button_Dio,Button->Button_Pin);
}

ButtonSw_state ButtonSw_Read(ButtonSw_datatype * Button)
{
	ButtonSw_state returnvar = SW_NOTPRESSED;
	
	if (DIO_pinRead(Button->Button_Dio,Button->Button_Pin) != Button->PrevButton_State)
	{
		_delay_ms(BUTTON_BOUNCE_PERIOD_mS);
		if (DIO_pinRead(Button->Button_Dio,Button->Button_Pin) != Button->PrevButton_State)
		{
			Button->PrevButton_State = DIO_pinRead(Button->Button_Dio,Button->Button_Pin);
			switch (Button->PrevButton_State)
			{
				case LOW:
				returnvar = SW_PRESSEDLOW;
				break;
				case HIGH:
				returnvar = SW_PRESSEDHIGH;
				break;
				default:
				break;
			}
		}
	}
	return returnvar;
}

void PushButton_Setup(PushButton_datatype Push)
					{
					 DIO_pinConfigure(Push.PushButton_Dio,Push.PushButton_Pin,INPUT_FLOAT);
					}
digitalState PushButton_Read(PushButton_datatype Push)
					{
						if(DIO_pinRead(Push.PushButton_Dio,Push.PushButton_Pin) == HIGH)
						{
							_delay_ms(BUTTON_BOUNCE_PERIOD_mS);
							if(DIO_pinRead(Push.PushButton_Dio,Push.PushButton_Pin) == HIGH)
							{
								return HIGH;
							}
							
						}
						
						return LOW;
					}