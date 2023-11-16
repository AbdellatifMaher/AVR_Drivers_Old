/*
 * SPI.c
 *
 * Created: 6/29/2020 3:33:02 PM
 *  Author: 8
 */ 

#include "uc_Configuration.h"
#include "SPI.h"
#include "GPIO_ATmega32A.h"

/*****************************************  Defines FOR SPI Interrupt Handling ************************************************/
#define SPI_VECTOR	  _VECTOR(12)



SPI_ConfigStruct SPI0 = {.SPI_TransfereInterruptCall = NULL};
	
/***************************************** SPI Interrupt ISR ************************************************/

ISR(SPI_VECTOR)
{
	if (SPI0.SPI_TransfereInterruptCall != NULL)
	{
		SPI0.SPI_TransfereInterruptCall();
	}
}


void SPI_Init(void)
{
		SPCR->allRegister = 0;
		SPSR->allRegister = 0;
		switch(SPI0.EnableControl)
		{
			case SPI_Disable:
			break;
			case SPI_Enable:
				 switch(SPI0.Mode)
				 {
					 case SPI_MASTER:
					 SPCR->allRegister |= (1<<MSTR);
					 DIO_pinConfigure(DIOB,PIN5,OUTPUT);
					 DIO_pinConfigure(DIOB,PIN4,OUTPUT);
					 DIO_pinConfigure(DIOB,PIN7,OUTPUT);
					 DIO_pinWrite(DIOB,PIN4,HIGH);
					 DIO_pinWrite(DIOB,PIN5,HIGH);
					 break;
					 case SPI_SLAVE:
					 DIO_pinConfigure(DIOB,PIN6,OUTPUT);
					 break;
				 }
				 switch(SPI0.DataOrder)
				 {
					 case SPI_LSB:
					 SPCR->allRegister |= (1<<DORD);
					 break;
					 case SPI_MSB:
					 break;
				 }
				 switch(SPI0.InterruptState)
				 {
					 case SPI_InterruptDisable:
					 break;
					 case SPI_InterruptEnable:
					 SPCR->allRegister |= (1<<SPIE);
					 break;
				 }
				 switch(SPI0.ClockMode)
				 {
					 case SPI_CLKMode0:
					 break;
					 case SPI_CLKMode1:
					 SPCR->allRegister |= (1<<CPHA);
					 break;
					 case SPI_CLKMode2:
					 SPCR->allRegister |= (1<<CPOL);
					 	/* 
						 * Note : if Used SPI Mode 3 or Mode 2 (CLK IDLE STATE = HIGH)
						 * in Some MicroControllers we must Explicitly State that The Default clk pin state is High 
						 * By Setting the pin to Output with a High Value 
						 */
					DIO_pinWrite(DIOB,PIN7,HIGH);
					 break;
					 case SPI_CLKMode3:
					 SPCR->allRegister |= (1<<CPHA) | (1<<CPOL);
					 DIO_pinWrite(DIOB,PIN7,HIGH);
					 break;
				 }
				 switch(SPI0.Freq)
				 {
					 case SPI_FCPU_BY_2:
					 SPSR->allRegister |= (1<<SPR2);
					 break;
					 case SPI_FCPU_BY_4:
					 break;
					 case SPI_FCPU_BY_8:
					 SPSR->allRegister |= (1<<SPR2);
					 SPCR->allRegister |= (1<<SPR0);
					 break;
					 case SPI_FCPU_BY_16:
					 SPCR->allRegister |= (1<<SPR0);
					 break;
					 case SPI_FCPU_BY_32:
					 SPSR->allRegister |= (1<<SPR2);
					 SPCR->allRegister |= (1<<SPR1);
					 break;
					 case SPI_FCPU_BY_64:
					 SPCR->allRegister |= (1<<SPR1);
					 break;
					 case SPI_FCPU_BY_128:
					 SPCR->allRegister |= (1<<SPR1) | (1<<SPR0);
					 break;
				 }
			/* Enable SPI Communication */
			SPCR->allRegister |= (1<<SPE);
			break;
		}
	
}
vuint8_t SPI_ReadWrite_Blocking(vuint8_t Data)
{
			/* Transmit Data Using SPI Bus */
			SPDR->allRegister = Data;
			
			/* Check if a Write Collision Error Occurred */
			if ( (SPSR->allRegister & (1<<WCOL) ) != 0)
			{
				SPI0.Error = SPI_WriteCollison;
			}
			
			/* Block till The End of Transmit ion */
			while ( (SPSR->allRegister & (1<<SPIF)) == 0 ) {}
			
			/* return Rx Data From SPI */
			return SPDR->allRegister;
}
vuint8_t SPI_ReadWrite_NonBlocking(vuint8_t Data)
{
					/* Transmit Data Using SPI Bus */
					SPDR->allRegister = Data;
					/* Check if a Write Collision Error Occurred */
					if ( (SPSR->allRegister & (1<<WCOL))  != 0)
					{
						SPI0.Error = SPI_WriteCollison;
					}
					/* return Rx Data From SPI */
					return SPDR->allRegister;
}