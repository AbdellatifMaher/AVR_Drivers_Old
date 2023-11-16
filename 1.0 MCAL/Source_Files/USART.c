/*
 * USART.c
 *
 * Created: 6/16/2020 2:33:21 PM
 *  Author: 8
 */ 

#include "USART.h"
#include "uc_Configuration.h"

/*****************************************  Defines FOR USART Interrupt Handling ************************************************/
			#define RXC_VECTOR	  _VECTOR(13)
			#define TXC_VECTOR	  _VECTOR(15)
			#define UDRE_VECTOR	  _VECTOR(14)
			
			

USART_ConfigurationStruct  UART0 = { 0,
										.RXC_InterruptCall  = NULL,
										.TXC_InterruptCall  = NULL,
									    .UDRE_InterruptCall = NULL };
										
										
/***************************************** USART Interrupt ISRs ************************************************/



ISR(RXC_VECTOR)
{
	if ( UART0.RXC_InterruptCall != NULL)
	{
		UART0.RXC_InterruptCall();
	}
}

ISR(TXC_VECTOR)
{
	if ( UART0.TXC_InterruptCall != NULL)
	{
		UART0.TXC_InterruptCall();
	}
}

ISR(UDRE_VECTOR)
{
	if ( UART0.UDRE_InterruptCall != NULL)
	{
		UART0.UDRE_InterruptCall();
	}
}

void USART_Init(void)
{
	vuint8_t UCSRA_Temp=0;
	vuint8_t UCSRB_Temp=0;
	vuint8_t UCSRC_Temp=0;
	float    UBRR_Temp=0;
	
	switch(UART0.EnableMode)
	{
		case USART_Disable:
		break;
		case USART_Rx_Only:
		UCSRB_Temp |= (1<<RXEN);
		break;
		case USART_Tx_Only:
		UCSRB_Temp |= (1<<TXEN);
		break;
		case USART_Tx_Rx:
		UCSRB_Temp |= (1<<RXEN) | (1<<TXEN);
		break;
		default:
		break;
	}
	
	switch (UART0.CommunicationMode)
	{
		case USART_Async_NormalSpeed:
		UBRR_Temp = (((float)F_CPU) / (16.0 * UART0.BaudRate)) - 0.5;
		break;
		case USART_Async_DoubleSpeed:
		UCSRA_Temp |= (1<<U2X);
		UBRR_Temp = (((float)F_CPU) / (8.0 * UART0.BaudRate)) - 0.5;
		break;
		case USART_Sync:
		UCSRC_Temp |= (1<<UMSEL);
		UBRR_Temp = (((float)F_CPU) / (2.0 * UART0.BaudRate)) - 0.5;
		switch (UART0.ClockPolarity)
		{
			case USART_SampleOnFalling:
			break;
			case USART_SampleOnRising:
			UCSRC_Temp |= (1<<UCPOL);
			break;
		}
		break;
		default:
		break;
	}
	switch(UART0.CommunicationTerminal)
	{
		case USART_SingleProcessor:
		break;
		case USART_MultiProcessor:
		UCSRA_Temp |= (1<<MPCM);
		break;
		default:
		break;
	}
	
	switch(UART0.InterruptSource)
	{
		case USART_InterruptDisable:
		break;
		case USART_RxComp_Enable:
		UCSRB_Temp |= (1<<RXCIE);
		break;
		case USART_TxComp_Enable:
		UCSRB_Temp |= (1<<TXCIE);
		break;
		case USART_UDREmpty_Enable:
		UCSRB_Temp |= (1<<UDRE);
		break;
		case USART_RxComp_TxComp_Enable:
		UCSRB_Temp |= (1<<TXCIE) | (1<<RXCIE);
		break;
		case USART_RxComp_UDREmpty_Enable:
		UCSRB_Temp |= (1<<UDRE) | (1<<RXCIE);
		break;
		case USART_TxComp_UDREmpty_Enable:
		UCSRB_Temp |= (1<<UDRE) | (1<<TXCIE);
		break;
		case USART_RxComp_TxComp_UDREmpty_Enable:
		UCSRB_Temp |= (1<<UDRE) | (1<<TXCIE) | (1<<RXCIE);
		break;
		default:
		break;
	}
	
	switch(UART0.DataFrame)
	{
		case USART_5bitData:
		break;
		case USART_6bitData:
		UCSRC_Temp |= (1<<UCSZ0);
		break;
		case USART_7bitData:
		UCSRC_Temp |= (1<<UCSZ1);
		break;
		case USART_8bitData:
		UCSRC_Temp |= (1<<UCSZ0) | (1<<UCSZ1);
		break;
		case USART_9bitData:
		UCSRC_Temp |= (1<<UCSZ0) | (1<<UCSZ1);
		UCSRB_Temp |= (1<<UCSZ2);
		break;
		default:
		break;
	}
	
	switch (UART0.ControlFrame)
	{
		case USART_ParityDisable_1Stop:
		break;
		case USART_ParityDisable_2Stop:
		UCSRC_Temp |= (1<<USBS);
		break;
		case USART_ParityEven_1Stop:
		UCSRC_Temp |= (1<<UPM1);
		break;
		case USART_ParityEven_2Stop:
		UCSRC_Temp |= (1<<USBS) | (1<<UPM1);
		break;
		case USART_ParityOdd_1Stop:
		UCSRC_Temp |= (1<<UPM0) | (1<<UPM1);
		break;
		case USART_ParityOdd_2Stop:
		UCSRC_Temp |= (1<<USBS) | (1<<UPM0) | (1<<UPM1);
		break;
	}
	
	UBRRH->allRegister = ((vuint16_t)UBRR_Temp)>>8;
	UBRRL->allRegister = ((vuint8_t)UBRR_Temp);
	UCSRA->allRegister = UCSRA_Temp;
	UCSRC->allRegister = UCSRC_Temp;
	UCSRB->allRegister = UCSRB_Temp;
}

void USART_SendByte_Blocking(vuint16_t Data)
{
	while((UCSRA->allRegister & (1<<UDRE)) == 0){}
	
	if (UART0.DataFrame == USART_9bitData)
	{
		UCSRB->allRegister = (UCSRB->allRegister & 0xFE) | ((Data & (1<<8)) >> 8);
	}
	UDR->allRegister = (vuint8_t) Data;
}


void USART_SendByte_NonBlocking(unsigned short Data)
{
	if ((UCSRA->allRegister & (1<<UDRE)) != 0)
	{
		if (UART0.DataFrame == USART_9bitData)
		{
			UCSRB->allRegister = (UCSRB->allRegister & 0xFE) | ((Data & (1<<8)) >> 8);
		}
		UDR->allRegister = (vuint8_t) Data;
	}
}


vuint16_t USART_ReadByte_Blocking(void)
{
	vuint16_t rxData = 0;
	
	while ( (UCSRA->allRegister & (1<<RXC)) == 0){}
	
	if (UCSRA->allRegister & ((1<<FE) | (1<<DOR) | (1<<PE)))
	{
		// Error : You Should Handle it as you Wish
		if (UCSRA->allRegister & (1<<FE))
		{
			UART0.ReadMsg_Error = USART_FrameError;
		}
		else if (UCSRA->allRegister & (1<<DOR))
		{
			UART0.ReadMsg_Error = USART_OverRunError;
		}
		else
		{
			UART0.ReadMsg_Error = USART_ParityError;
		}
	}
	
	if (UART0.DataFrame == USART_9bitData)
	{
		rxData =  UCSRB->allRegister & (1<<RXB8) << 7;
	}
	rxData |= UDR->allRegister;
	return rxData;
}



vuint16_t USART_ReadByte_NonBlocking(void)
{
	vuint16_t rxData = 0;
	
	if ( (UCSRA->allRegister & (1<<RXC)) != 0)
	{
	
	if (UCSRA->allRegister & ((1<<FE) | (1<<DOR) | (1<<PE)))
	{
		// Error : You Should Handle it as you Wish
		if (UCSRA->allRegister & (1<<FE))
		{
			UART0.ReadMsg_Error = USART_FrameError;
		}
		else if (UCSRA->allRegister & (1<<DOR))
		{
			UART0.ReadMsg_Error = USART_OverRunError;
		}
		else
		{
			UART0.ReadMsg_Error = USART_ParityError;
		}
	}
	
	if (UART0.DataFrame == USART_9bitData)
	{
		rxData =  UCSRB->allRegister & (1<<RXB8) << 7;
	}
	rxData |= UDR->allRegister;
	}
	return rxData;
}