/*
 * PushButton.h
 *
 * Created: 8/11/2020 6:29:41 PM
 *  Author: 8
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "uc_Configuration.h"
#include "GPIO_ATmega32A.h"
#include "util/delay.h"

typedef enum
{
	SW_NOTPRESSED,
	SW_PRESSEDHIGH,
	SW_PRESSEDLOW
}ButtonSw_state;


typedef struct
{
	DIO *	 Button_Dio;
	pinNumber Button_Pin;
	pinMode	 InputMode;
	digitalState PrevButton_State;
}ButtonSw_datatype;

typedef struct
{
	DIO *	  PushButton_Dio;
	pinNumber PushButton_Pin;
}PushButton_datatype;


void ButtonSw_Setup(ButtonSw_datatype * Button);
ButtonSw_state ButtonSw_Read(ButtonSw_datatype * Button);
void Button_UserWarningError(void);
void PushButton_Setup(PushButton_datatype Push) ;
digitalState PushButton_Read(PushButton_datatype Push);


#endif /* PUSHBUTTON_H_ */