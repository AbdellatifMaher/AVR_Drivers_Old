/*
 * GPIO_ATmega32A.c
 *
 * Created: 6/9/2020 7:50:20 PM
 *  Author: Andellatif
 */ 

#include "GPIO_ATmega32A.h"

void	DIO_pinConfigure(
							DIO * Dio,
							pinNumber pinNum,
							pinMode Mode){
								
								switch(Mode)
								{

									case INPUT_FLOAT:
									CLEARBIT(Dio->ddr.allRegister,pinNum);
									CLEARBIT(Dio->port.allRegister,pinNum);
									break;
									case INPUT_PULLUP:
									CLEARBIT(Dio->ddr.allRegister,pinNum);
									SETBIT(Dio->port.allRegister,pinNum);
									break;
									case OUTPUT:
									SETBIT(Dio->ddr.allRegister,pinNum);
									CLEARBIT(Dio->port.allRegister,pinNum);
									break;
									default:  break;
								}
								}

void	DIO_pinWrite(
						DIO * Dio,
						pinNumber pinNum,
						digitalState State)
						{
									switch(State)
									{
										case HIGH:
										SETBIT(Dio->port.allRegister,pinNum);
										break;
										case LOW:
										CLEARBIT(Dio->port.allRegister,pinNum);
										break;
										default: break;
									}
						}

digitalState DIO_pinRead(
							DIO * Dio,
							pinNumber pinNum)
							{
								digitalState returnvar = 0;
										switch(READBIT(Dio->pin.allRegister,pinNum))
										{
											case LOW:
											returnvar = LOW;
											break;
											case HIGH:
											returnvar = HIGH;
											break;
											default:
											break;
										}
										return returnvar;
							}

void	DIO_portConfigure(
								DIO * Dio,
								vuint8_t ConfigByte)
								{
									Dio->ddr.allRegister =ConfigByte ;
								}

void	DIO_portWrite(
							DIO * Dio,
							vuint8_t Data)
							{
								Dio->port.allRegister=Data;
							}

vuint8_t DIO_portRead  (DIO * Dio)
							{
								return  Dio->pin.allRegister;
							}
