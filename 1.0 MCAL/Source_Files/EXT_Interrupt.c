/*
 * EXT_Interrupt.c
 *
 * Created: 6/16/2020 12:39:02 PM
 *  Author: 8
 */ 


#include "EXT_Interrupt.h"

/*****************************************  Defines FOR External Interrupt Handling ************************************************/


#define INT0VECTOR	_VECTOR(1)
#define INT1VECTOR	_VECTOR(2)
#define INT2VECTOR	_VECTOR(3)


void (*volatile EXTINT0_Functionp)(void)=NULL;
void (*volatile EXTINT1_Functionp)(void)=NULL;
void (*volatile EXTINT2_Functionp)(void)=NULL;

/***************************************** AVR External Interrupt ISRs ************************************************/



ISR(INT0VECTOR)
{
	if (EXTINT0_Functionp != NULL)
	{
		EXTINT0_Functionp();
	}
}

ISR(INT1VECTOR)
{
	if (EXTINT1_Functionp != NULL)
	{
		EXTINT1_Functionp();
	}
}

ISR(INT2VECTOR)
{
	if (EXTINT2_Functionp != NULL)
	{
		EXTINT2_Functionp();
	}
}

/***************************************** External Interrupt Functions ************************************************/


void ExternalInterrupt_Configure(ExtInt_Number IntNumber,ExtInt_Mode Mode)
{
	switch(IntNumber)
	{
		case EXTINT0:
		// Disable Int0
		CLEARBIT(GICR->allRegister,PIN6);
		// Configure Int0
		switch (Mode)
		{
			case EXTINT_LOWLVL:
			CLEARBIT(MCUCR->allRegister,PIN0);
			CLEARBIT(MCUCR->allRegister,PIN1);
			break;
			case EXTINT_BOTHEDGE:
			SETBIT(MCUCR->allRegister,PIN0);
			CLEARBIT(MCUCR->allRegister,PIN1);
			break;
			case EXTINT_FALLING:
			CLEARBIT(MCUCR->allRegister,PIN0);
			SETBIT(MCUCR->allRegister,PIN1);
			break;
			case EXTINT_RISING:
			SETBIT(MCUCR->allRegister,PIN0);
			SETBIT(MCUCR->allRegister,PIN1);
			break;
			default:
			break;
		}
		// Enable int0
		SETBIT(GICR->allRegister,PIN6);
		break;
		case EXTINT1:
		CLEARBIT(GICR->allRegister,PIN7);
		switch (Mode)
		{
			case EXTINT_LOWLVL:
			CLEARBIT(MCUCR->allRegister,PIN2);
			CLEARBIT(MCUCR->allRegister,PIN3);
			break;
			case EXTINT_BOTHEDGE:
			SETBIT(MCUCR->allRegister,PIN2);
			CLEARBIT(MCUCR->allRegister,PIN3);
			break;
			case EXTINT_FALLING:
			CLEARBIT(MCUCR->allRegister,PIN2);
			SETBIT(MCUCR->allRegister,PIN3);
			break;
			case EXTINT_RISING:
			SETBIT(MCUCR->allRegister,PIN2);
			SETBIT(MCUCR->allRegister,PIN3);
			break;
			default:
			break;
		}
		SETBIT(GICR->allRegister,PIN7);
		break;
		case EXTINT2:
		CLEARBIT(GICR->allRegister,PIN5);
		switch (Mode)
		{
			case EXTINT_FALLING:
			CLEARBIT(MCUCSR->allRegister,PIN6);
			break;
			case EXTINT_RISING:
			SETBIT(MCUCSR->allRegister,PIN6);
			break;
			case EXTINT_LOWLVL:
			case EXTINT_BOTHEDGE:
			default:
			break;
		}
		SETBIT(GICR->allRegister,PIN5);
		break;
	}
}

void ExternalInterrupt_Disable(ExtInt_Number IntNumber)
{
	switch(IntNumber)
	{
		case EXTINT0:
		CLEARBIT(GICR->allRegister,PIN6);
		break;
		case EXTINT1:
		CLEARBIT(GICR->allRegister,PIN7);
		break;
		case EXTINT2:
		CLEARBIT(GICR->allRegister,PIN5);
		break;
	}
}
