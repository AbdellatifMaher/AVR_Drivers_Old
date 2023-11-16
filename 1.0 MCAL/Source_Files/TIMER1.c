/*
 * TIMER1.c
 *
 * Created: 8/7/2020 11:41:01 AM
 *  Author: 8
 */ 

#include "uc_Configuration.h"
#include "TIMER1.h"

#define TIMER1_IC1_VECT		_VECTOR(6)
#define TIMER1_COMPA_VECT	_VECTOR(7)
#define TIMER1_COMPB_VECT	_VECTOR(8)
#define TIMER1_OVF_VECT		_VECTOR(9)

 void (* Timer1_InputCapture_CallBack)(void)=NULL;
 void (* Timer1_CompA_CallBack)       (void)=NULL;
 void (* Timer1_CompB_CallBack)       (void)=NULL;
 void (* Timer1_OVF_CallBack)         (void)=NULL ;
 
 
  ISR(TIMER1_IC1_VECT)
  {
	  if (Timer1_InputCapture_CallBack != NULL)
	  {
		  Timer1_InputCapture_CallBack();
	  }
  }
 
 ISR(TIMER1_COMPA_VECT)
 {
	 if (Timer1_CompA_CallBack != NULL)
	 {
		 Timer1_CompA_CallBack() ;
	 }
 }
  ISR(TIMER1_COMPB_VECT)
  {
	  if (Timer1_CompB_CallBack != NULL)
	  {
		  Timer1_CompB_CallBack() ;
	  }
  }
 ISR(TIMER1_OVF_VECT)
 {
	 if (Timer1_OVF_CallBack != NULL)
	 {
		 Timer1_OVF_CallBack();
	 }
 }


void Timer1_Init(Timer1_Modes T1mode,Timer1_FreqSelect T1freq,Timer1_COMPMode TCOMP,Timer1_OC1ABControlMode TOC1mode,Timer1_Interrupt Tinterrupt)
				{
					switch(TCOMP)
					{
						case    NO_COMP :TCCR1A->allRegister |= T1mode; break;
						case    COMPA   :TCCR1A->allRegister |= (TOC1mode <<2) | T1mode ; break;
						case    COMPB   :TCCR1A->allRegister |= TOC1mode | T1mode ; break;
						case COMPA_COMPB:TCCR1A->allRegister |= TOC1mode | T1mode ; TCCR1A->allRegister |= TOC1mode <<2; break;
						default         :break;
					} 
					TCCR1B->allRegister |= (T1mode >> 8) | T1freq ;
					TIMSK->allRegister &=0x3C;
					TIMSK->allRegister |=Tinterrupt;
				}

vuint16_t Timer1_InputCapture (Timer1_InputCapture_Mode TIC)
							{
								vuint16_t t=0;
								switch(TIC) 
								{
									case FALLING_EDGE_WITH_NOISE_CANCELER    :
									case RISING_EDGE_WITH_NOISE_CANCELER     : //delay 
									case FALLING_EDGE_WITH_NO_NOISE_CANCELER :  
									case RISING_EDGE_WITH_NO_NOISE_CANCELER  : TCCR1B->allRegister |= TIC; break;
									default                                  : break;
								}
								
								while( (TIFR->allRegister & (1<< ICF1)) == 0 ) ;
								SETBIT(TIFR->allRegister,ICF1);
								t=ICR1L->allRegister;
								t|=ICR1H->allRegister;
								return t;
							}
							
void Timer1_Delay(vuint64_t second)
	{
		//set prescaler to 256 and start the timer
		TCCR1A->allRegister= 0x00;
		TCCR1B->allRegister= 0x04;
		
		for(vuint64_t i=1;i<=second;i++)
		{
			while( ( TIFR->allRegister & (1<<TOV1) ) == 0) //wait for the overflow event
			{
				
			}
			SETBIT(TIFR->allRegister,TOV1);
			//reset the overflow flag
		}
	}
	
void Timer1_SetCompareA_Value (vuint16_t CompareA)
{
	OCR1AH->allRegister = CompareA >>8;
	OCR1AL->allRegister = CompareA;
}

void Timer1_SetCompareB_Value (vuint16_t CompareB)
{
	OCR1BH->allRegister = CompareB >>8;
	OCR1BL->allRegister = CompareB;
}

void Timer1_CTC_CompA_SquareGenerate(float32 SignalFreq, float32 Timer1_Freq)
{
	OCR1AH->allRegister =	 ((vuint16_t)	((Timer1_Freq/(2.0*SignalFreq)) - 0.5) ) >>8;
	OCR1AL->allRegister =	 ((vuint16_t)	((Timer1_Freq/(2.0*SignalFreq)) - 0.5) );
}

void Timer1_CTC_CompB_SquareGenerate(float32 SignalFreq, float32 Timer1_Freq)
{
	OCR1BH->allRegister =	 ((vuint16_t)	((Timer1_Freq/(2.0*SignalFreq)) - 0.5) ) >>8;
	OCR1BL->allRegister =	 ((vuint16_t)	((Timer1_Freq/(2.0*SignalFreq)) - 0.5) );
}


void Timer1_PWMSetDutyCycleA(float DutyCycle,Timer1_OC1ABControlMode InvertionState,vuint16_t TOP)
{
	switch (InvertionState)
	{
		case Timer1_PWM_NonInvert:
		OCR1AH->allRegister = ((vuint16_t)(((DutyCycle/100.0) * TOP)+0.5 )) >>8 ;
		OCR1AL->allRegister = ((vuint16_t)((DutyCycle/100.0) * TOP)+0.5 );
		break;
		case Timer1_PWM_Invert:
		OCR1AH->allRegister = ((vuint16_t)(((100-DutyCycle/100.0) * TOP)+0.5 )) >>8 ;
		OCR1AL->allRegister = ((vuint16_t)((100-DutyCycle/100.0) * TOP)+0.5 );
		break;
		default:
		break;
	}
}

void Timer1_PWMSetDutyCycleB(float DutyCycle,Timer1_OC1ABControlMode InvertionState,vuint16_t TOP)
{
	switch (InvertionState)
	{
		case Timer1_PWM_NonInvert:
		OCR1BH->allRegister = ((vuint16_t)(((DutyCycle/100.0) * TOP)+0.5 )) >>8 ;
		OCR1BL->allRegister = ((vuint16_t)((DutyCycle/100.0) * TOP)+0.5 );
		break;
		case Timer1_PWM_Invert:
		OCR1BH->allRegister = ((vuint16_t)(((100-DutyCycle/100.0) * TOP)+0.5 )) >>8 ;
		OCR1BL->allRegister = ((vuint16_t)((100-DutyCycle/100.0) * TOP)+0.5 );
		break;
		default:
		break;
	}
}