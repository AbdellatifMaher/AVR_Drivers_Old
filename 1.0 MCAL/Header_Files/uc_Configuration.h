/*
 * uc_Configuration.h
 *
 * Created: 6/9/2020 3:12:43 PM
 *  Author: 8
 */ 


#ifndef UC_CONFIGURATION_H_
#define UC_CONFIGURATION_H_

#define _AVR_ATMEGA32A_H_INCLUDED

#include <MACROS.h>
#include <StdTypes.h>

/******************************* CPU Related Defines *******************************************************/
#define F_CPU		(16000000U)

/******************************* CPU Internal Registers <SFRs & GPRs> **************************************/
#define IO_OFFSET	(0x20)
#define SRAM_OFFSET	(0x60)
#define CPU_REG		((vuint8_t *)0x00)
#define NULL	((void *) 0x0FFF)

#define SREG				((reg8*)(0x3F+IO_OFFSET))
#define MCUCR				((reg8*)(0x35+IO_OFFSET))
#define MCUCSR				((reg8*)(0x34+IO_OFFSET))
#define GICR				((reg8*)(0x3B+IO_OFFSET))
#define GIFR				((reg8*)(0x3A+IO_OFFSET))

#define UDR				    ((reg8*)(0x0C+IO_OFFSET))
#define UCSRA				((reg8*)(0x0B+IO_OFFSET))
#define UCSRB				((reg8*)(0x0A+IO_OFFSET))
#define UCSRC				((reg8*)(0x20+IO_OFFSET))
#define UBRRH				((reg8*)(0x20+IO_OFFSET))
#define UBRRL				((reg8*)(0x09+IO_OFFSET))


#define SPCR				((reg8*)(0x0D +IO_OFFSET))
#define SPSR				((reg8*)(0x0E +IO_OFFSET))
#define SPDR				((reg8*)(0x0F +IO_OFFSET))


#define EEARH  ((reg8*)((0x1F)+ IO_OFFSET))
#define EEARL  ((reg8*)((0x1E)+ IO_OFFSET))
#define EEDR   ((reg8*)((0x1D)+ IO_OFFSET))
#define EECR   ((reg8*)((0x1C)+ IO_OFFSET))
#define SPMCR  ((reg8*)((0x37)+ IO_OFFSET))


#define TWBR  ((reg8*)((0x00)+ IO_OFFSET))
#define TWSR  ((reg8*)((0x01)+ IO_OFFSET))
#define TWAR  ((reg8*)((0x02)+ IO_OFFSET))
#define TWDR  ((reg8*)((0x03)+ IO_OFFSET))
#define TWCR  ((reg8*)((0x36)+ IO_OFFSET))




#define  TCCR0		((reg8 *) (0x33 + IO_OFFSET))
#define  TCNT0		((reg8 *) (0x32 + IO_OFFSET))
#define  OCR0		((reg8 *) (0x3C + IO_OFFSET))
#define  TIMSK		((reg8 *) (0x39 + IO_OFFSET))
#define  TIFR		((reg8 *) (0x38 + IO_OFFSET))

#define  TCCR1A		((reg8 *) (0x2F + IO_OFFSET))
#define  TCCR1B		((reg8 *) (0x2E + IO_OFFSET))
#define  TCNT1H		((reg8 *) (0x2D + IO_OFFSET))
#define  TCNT1L		((reg8 *) (0x2C + IO_OFFSET))
#define  OCR1AH		((reg8 *) (0x2B + IO_OFFSET))
#define  OCR1AL		((reg8 *) (0x2A + IO_OFFSET))
#define  OCR1BH		((reg8 *) (0x29 + IO_OFFSET))
#define  OCR1BL		((reg8 *) (0x28 + IO_OFFSET))
#define  ICR1H		((reg8 *) (0x27 + IO_OFFSET))
#define  ICR1L		((reg8 *) (0x26 + IO_OFFSET))

#define  TCCR2		((reg8 *) (0x25 + IO_OFFSET))
#define  TCNT2		((reg8 *) (0x24 + IO_OFFSET))
#define  OCR2		((reg8 *) (0x23 + IO_OFFSET))


/*****************************************  Attribute Defines FOR AVR Interrupt Handling ************************************************/
#define ISR_NONBLOCK 	__attribute__((interrupt))
#define ISR_BLOCK
#define ISR_NAKED      	__attribute__((naked))
#define ISR_ALIASOF(v) 	__attribute__((alias(__STRINGIFY(v))))
#define _VECTOR(N) 		__vector_ ## N

#define ISR(V,...)	void V (void) __attribute__ ((signal)) __VA_ARGS__;\
					void V (void)


/******************************************* Global Interrupt Related Macros **************************************/
#define GLOBAL_INTERRUPT_ENABLE()	{SREG->bits.b7=1;}
#define GLOBAL_INTERRUPT_DISABLE()	{SREG->bits.b7=0;}



/******************************************* User Types For AVR MCU **************************************/

typedef union 
{
	vuint8_t allRegister;
	struct
	{
		vuint8_t b0:1;
		vuint8_t b1:1;
		vuint8_t b2:1;
		vuint8_t b3:1;
		vuint8_t b4:1;
		vuint8_t b5:1;
		vuint8_t b6:1;
		vuint8_t b7:1;
	}bits;
           }reg8; 
	
	typedef struct
	{
		reg8 pin;
		reg8 ddr;
		reg8 port;
	}DIO;




#endif /* UC_CONFIGURATION_H_ */