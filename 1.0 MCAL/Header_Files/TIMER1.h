/*
 * TIMER1.h
 *
 * Created: 8/7/2020 11:40:37 AM
 *  Author: 8
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

  #define ICF1  5
  #define OCF1A 4
  #define OCF1B 3
  #define TOV1  2
 
 typedef enum
 {
	 Timer1_NormalMode=0x0000,
	 Timer1_PWMPhaseCorrect_8bit=0x0001,
	 Timer1_PWMPhaseCorrect_9bit=0x0002,
	 Timer1_PWMPhaseCorrect_10bit=0x0003,
	 Timer1_CTCMode_OCR1=0x0800,
	 Timer1_PWMFast_8bit=0x0801,
	 Timer1_PWMFast_9bit=0x0802,
	 Timer1_PWMFast_10bit=0x0803,
	 Timer1_PWMPhaseandFreqCorrect_ICR1=0x1000,
	 Timer1_PWMPhaseandFreqCorrect_OCR1=0x1001,
	 Timer1_PWMPhaseCorrect_ICR1=0x1002,
	 Timer1_PWMPhaseCorrect_OCR1=0x1003,
	 Timer1_CTCMode_ICR1=0x1800,
	 Timer1_PWMFast_ICR1=0x1802,
	 Timer1_PWMFast_OCR1=0x1803,
 }Timer1_Modes;
 
 typedef enum 
 {
	 NO_COMP,
	 COMPA,
	 COMPB,
	 COMPA_COMPB,
	 }Timer1_COMPMode;
 
 typedef enum
 {
	 Timer1_OC1ABDisconnect=0x00,
	 Timer1_NonPWM_ToggleOC1AB=0x10,
	 Timer1_NonPWM_ClearOC1AB=0x20,
	 Timer1_NonPWM_SetOC1AB=0x30,
	 Timer1_PWM_ToggleOC1A_OC1BDisconnect=0x10,
	 Timer1_PWM_NonInvert=0x20,
	 Timer1_PWM_Invert=0x30,
 }Timer1_OC1ABControlMode;
 
 typedef enum 
 {
	 FALLING_EDGE_WITH_NO_NOISE_CANCELER,
	 FALLING_EDGE_WITH_NOISE_CANCELER=0x80,
	 RISING_EDGE_WITH_NO_NOISE_CANCELER=0x40,
	 RISING_EDGE_WITH_NOISE_CANCELER=0xC0,
	  }Timer1_InputCapture_Mode;
 
 typedef enum
 {
	 Timer1_Disable,
	 Timer1_FCPU,
	 Timer1_FCPU_BY8,
	 Timer1_FCPU_BY64,
	 Timer1_FCPU_BY256,
	 Timer1_FCPU_BY1024,
	 Timer1_EXTCLK_Falling,
	 Timer1_EXTCLK_Rising,
 }Timer1_FreqSelect;
 
 
 	typedef enum
 	{
	 	Timer1_InterruptDisable,
	 	Timer1_OVFInterruptEnable=0x04,
	 	Timer1_COMPB_InterruptEnable=0x08,
		Timer1_COMPA_InterruptEnable=0x10,
		Timer1_InputCapture_InterruptEnable=0x20,
	 	Timer1_OVF_COMPB_InterruptEnable=0x0C,
		Timer1_OVF_COMPA_InterruptEnable=0x14,
	    Timer1_OVF_COMPA_COMPB_InterruptEnable=0x1C,
		Timer1_OVF_COMPB_IC_InterruptEnable=0x2C,
		Timer1_OVF_COMPA_IC_InterruptEnable=0x34,
		Timer1_OVF_COMPA_COMPB_IC_InterruptEnable=0x3C,
		Timer1_COMPA_COMPB_IC_InterruptEnable=0x38,
		Timer1_COMPB_IC_InterruptEnable=0x28,
		Timer1_COMPA_IC_InterruptEnable=0x30,
		Timer1_OVF_IC_InterruptEnable=0x24,
 	}Timer1_Interrupt;
 	
 	
 	extern void (* Timer1_OVF_CallBack)(void) ;
 	extern void (* Timer1_CompA_CallBack)(void);
	extern void (* Timer1_CompB_CallBack)(void);
    extern void (* Timer1_InputCapture_CallBack)(void);
	
	void        Timer1_Init     (Timer1_Modes T1mode,
								Timer1_FreqSelect T1freq,
								Timer1_COMPMode TCOMP,
								Timer1_OC1ABControlMode TOC1mode,
								Timer1_Interrupt Tinterrupt);
	vuint16_t Timer1_InputCapture (Timer1_InputCapture_Mode TIC);
	void Timer1_Delay(vuint64_t second);
	void Timer1_SetCompareA_Value (vuint16_t CompareA);
	void Timer1_SetCompareB_Value (vuint16_t CompareB);
	void Timer1_CTC_CompA_SquareGenerate(float32 SignalFreq, float32 Timer1_Freq);
	void Timer1_CTC_CompB_SquareGenerate(float32 SignalFreq, float32 Timer1_Freq);
	void Timer1_PWMSetDutyCycleA(float DutyCycle,Timer1_OC1ABControlMode InvertionState,vuint16_t TOP);
	void Timer1_PWMSetDutyCycleB(float DutyCycle,Timer1_OC1ABControlMode InvertionState,vuint16_t TOP);




#endif /* TIMER1_H_ */