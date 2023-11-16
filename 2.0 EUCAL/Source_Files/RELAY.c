/*
 * RELAY.c
 *
 * Created: 9/3/2020 9:52:45 PM
 *  Author: 8
 */ 

#include "uc_Configuration.h"
#include "GPIO_ATmega32A.h"
#include "RELAY.h"
void RelaySetup(void)
					{
						DIO_pinConfigure(RELAYPORT,RELAYPIN,OUTPUT);
					}
void RelayControl(digitalState state)
					{
						switch(state)
						{
							case LOW : DIO_pinWrite(RELAYPORT,RELAYPIN,LOW);break;
							case HIGH: DIO_pinWrite(RELAYPORT,RELAYPIN,HIGH);break;
							default  : break;
						}
							
					}