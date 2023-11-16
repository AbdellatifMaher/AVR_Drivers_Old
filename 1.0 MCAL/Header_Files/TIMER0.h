/*
 * TIMER0.h
 *
 * Created: 8/6/2020 3:03:13 PM
 *  Author: 8
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

   #define TOV0 0
   #define OCF0 1
   
   
   
	typedef enum
	{
		Timer0_NormalMode=0x00,
		Timer0_CTCMode=0x08,
		Timer0_PWMPhaseCorrect=0x40,
		Timer0_PWMFast=0x48,
	}Timer0_Modes;
	
	
	typedef enum
	{
		Timer0_OC0Disconnect=0x00,
		Timer0_NonPWM_ToggleOC0=0x10,
		Timer0_NonPWM_ClearOC0=0x20,
		Timer0_NonPWM_SetOC0=0x30,
		Timer0_PWM_NonInvert=0x20,
		Timer0_PWM_Invert=0x30,
	}Timer0_OC0ControlMode;

	typedef enum
	{
		Timer0_Disable,
		Timer0_FCPU,
		Timer0_FCPU_BY8,
		Timer0_FCPU_BY64,
		Timer0_FCPU_BY256,
		Timer0_FCPU_BY1024,
		Timer0_EXTCLK_Falling,
		Timer0_EXTCLK_Rising,
	}Timer0_FreqSelect;

	typedef enum
	{
		Timer0_InterruptDisable,
		Timer0_OVFInterruptEnable,
		Timer0_COMPInterruptEnable,
		Timer0_OVF_COMP_InterruptEnable,
	}Timer0_Interrupt;
	
	
	extern void (* Timer0_OVF_CallBack)(void) ;
	extern void (* Timer0_Comp_CallBack)(void);
	
	void Timer0_Init
						(		Timer0_FreqSelect Tfreq,
								Timer0_Modes  Tmode,
								Timer0_OC0ControlMode TOc0Mode,
								Timer0_Interrupt      Tinterrupt
						);
	
	void Timer0_SetCompareValue (uint8_t Compare);
	
	void Timer0_CTC_SquareGenerate(float32 SignalFreq, float32 Timer0_Freq);
	
	void Timer0_Delay(vuint64_t millisecond);
	
	void Timer0_PWMSetDutyCycle(float DutyCycle,Timer0_OC0ControlMode InvertionState);




#endif /* TIMER0_H_ */