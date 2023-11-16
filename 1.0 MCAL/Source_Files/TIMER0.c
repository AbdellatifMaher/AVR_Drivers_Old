/*
 * TIMER0.c
 *
 * Created: 8/6/2020 3:06:29 PM
 *  Author: 8
 */ 

#include "uc_Configuration.h"
#include "TIMER0.h"


#define TIMER0_OVF_VECT		_VECTOR(11)
#define TIMER0_COMP_VECT	_VECTOR(10)

void (* Timer0_OVF_CallBack)(void) = NULL;
void (* Timer0_Comp_CallBack)(void)= NULL;

ISR(TIMER0_COMP_VECT)
{
	if (Timer0_Comp_CallBack != NULL)
	{
		Timer0_Comp_CallBack();
	}
}
ISR(TIMER0_OVF_VECT)
{
	if (Timer0_OVF_CallBack != NULL)
	{
		Timer0_OVF_CallBack();
	}
}

void Timer0_Init(Timer0_FreqSelect Tfreq,Timer0_Modes  Tmode,Timer0_OC0ControlMode TOc0Mode,Timer0_Interrupt  Tinterrupt)
{
	TCCR0->allRegister = Tfreq | Tmode | TOc0Mode;
	TIMSK->allRegister &= 0xFC;
	TIMSK->allRegister |= Tinterrupt;
}


void Timer0_SetCompareValue (vuint8_t Compare)
{
	OCR0->allRegister = Compare;
}


void Timer0_CTC_SquareGenerate(float32 SignalFreq, float32 Timer0_Freq)
{
	OCR0->allRegister =	(vuint8_t)	((Timer0_Freq/(2.0*SignalFreq)) - 0.5);
}


void Timer0_Delay(vuint64_t millisecond)
{
	//set prescaler to 64 and start the timer 
	TCCR0->allRegister= 0x03;
	
	for(vuint64_t i=1;i<=millisecond;i++) 
	{
		while( ( TIFR->allRegister & (1<<TOV0) ) == 0) //wait for the overflow event 
		{
			
		}
		SETBIT(TIFR->allRegister,TOV0);
		//reset the overflow flag 
	}
}

void Timer0_PWMSetDutyCycle(float DutyCycle,Timer0_OC0ControlMode InvertionState)
{
	switch (InvertionState)
	{
		case Timer0_PWM_NonInvert:
		OCR0->allRegister = ((DutyCycle/100.0) * 255)+0.5;
		break;
		case Timer0_PWM_Invert:
		OCR0->allRegister = (((100-DutyCycle)/100.0) * 255)+0.5;
		break;
		default:
		break;
	}
}