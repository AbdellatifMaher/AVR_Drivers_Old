/*
 * _7_SEGMENT.c
 *
 * Created: 6/10/2020 4:58:16 PM
 *  Author: Abdellatif 
 */ 

#include "SEVEN_SEGMENT.h"

 void Segment_Configure(DIO *dio)
								{
									vuint8_t OUT=0b11111111 ;
									DIO_portConfigure(dio,OUT);
								}
 void Segment_display(DIO *dio,vuint8_t Number)
											  {
												switch(Number)
												{
													case 0: dio->port.allRegister = 0b01111110 ; break;
													case 1: dio->port.allRegister = 0b00001100 ; break;
													case 2: dio->port.allRegister = 0b10110110 ; break;
													case 3: dio->port.allRegister = 0b10011110 ; break;
													case 4: dio->port.allRegister = 0b11001100 ; break;
													case 5: dio->port.allRegister = 0b11011010 ; break;
													case 6: dio->port.allRegister = 0b11111010 ; break;
													case 7: dio->port.allRegister = 0b00001110 ; break;
													case 8: dio->port.allRegister = 0b11111110 ; break;
													case 9: dio->port.allRegister = 0b11011110 ; break;
												}	
												}
												
void Dot_Segment(DIO *dio,digitalState state)
											{
												if(state)
												{
													SETBIT(dio->port.allRegister,PIN0);
												}
												else
												{
													CLEARBIT(dio->port.allRegister,PIN0);
												}
												}