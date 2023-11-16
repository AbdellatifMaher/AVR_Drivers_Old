/*
 * USARTAPP.c
 *
 * Created: 8/11/2020 5:37:13 PM
 *  Author: 8
 */ 

/*
#include "USART.h"
//#include <util/delay.h>

char x='B';
void inter1(void)
{
	USART_SendByte_NonBlocking(x);
}
void inter2(void)
{
	x=USART_ReadByte_NonBlocking();
}
int main(void)
{
	UART0.BaudRate=9600;
	UART0.CommunicationTerminal=USART_SingleProcessor;
	UART0.CommunicationMode=USART_Async_DoubleSpeed;
	UART0.DataFrame=USART_8bitData;
	UART0.ControlFrame=USART_ParityDisable_1Stop;
	UART0.EnableMode=USART_Tx_Rx;
	UART0.InterruptSource=USART_RxComp_TxComp_Enable;


	
	UART0.RXC_InterruptCall=inter2;
	UART0.TXC_InterruptCall=inter1;
	USART_Init();
	while(1)
	{
		
		USART_SendByte_Blocking(x);
		x= USART_ReadByte_Blocking();
		//TODO:: Please write your application code
	}
}  */