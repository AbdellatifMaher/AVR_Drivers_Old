/*
 * main.c
 *
 * Created: 11/7/2019 8:10:43 PM
 *  Author: Hamdy
 */ 


#include "LCD.h"
#include <util/delay.h>
#include "ATMEGA32_ADC.h"
#include "ATMega32Sleeep.h"
#include "uc_Configuration.h"
float32 g;
void interrfun(uint16 f)
{
	g=(float32)f * 5.0 / 1024.0 ;

}
int main()
{
	
	LCD_init();
	//ADC_Init(AVCC,ADC_SingleConv,ADC_FCPU_BY128,ADC_InterruptDisable);
	ADC_Init(AVCC,ADC_SingleConv,ADC_FCPU_BY128,ADC_InterruptEnable);
	
	//uint16 ADC_Result = 0;
	GLOBAL_INTERRUPT_ENABLE();

	while(1)
	{
		//ADC_Result = ADC_Read_Polling(ADC0, ADC_10BITS);
		ADC_Read_Interrupt(ADC0,ADC_10BITS);
		ADC_CallBack= interrfun;
		//LCD_DisplayString("Welcome:");
		//LCD_Select_RowCol(1,0);
		LCD_DisplayNumber(g,LCD_DecimalBase);
		LCD_DisplayNumber(9.58687,LCD_DecimalBase);
		//LCD_DisplayNumber((50*ADC_Result)/(1024),LCD_DecimalBase);
		
		_delay_ms(250);
		LCD_Clear();
	}	
}
