/*
 * KEYPAD.c
 *
 * Created: 8/15/2020 9:48:23 PM
 *  Author: 8
 */ 

#include "uc_Configuration.h"
#include "GPIO_ATmega32A.h"
#include "KEYPAD.h"
#include "util/delay.h"
void Key_Configure(DIO *PAD)
				{
					vuint8_t D=0xF0;
					DIO_portConfigure(PAD,D);
					D=0xFF;
					DIO_portWrite(PAD,D);
					}
							
vuint8_t Key_PRESSED(DIO *PAD)
					{
						uint8_t i,j,R=9,C=9,ch=0,flag=0;
						pinNumber RPIN[4]={PIN0,PIN1,PIN2,PIN3};
						pinNumber CPIN[4]={PIN4,PIN5,PIN6,PIN7};
							for(i=0;i<4;i++)
							{
								DIO_pinWrite(PAD,CPIN[i],LOW);
								for(j=0;j<4;j++)
								{
									
									if(DIO_pinRead(PAD,RPIN[j])==0)
									{
										_delay_ms(60);
										if(DIO_pinRead(PAD,RPIN[j])==0)
									  { 
										R=j;
										C=i;
										flag=1;
										break;
									  }
									}
									}
									DIO_pinWrite(PAD,CPIN[i],HIGH);
									if(flag == 1)
									{
										break;
									}
								}
								switch(R)
								{
									case 0 : switch(C)
											{
												case 0 : ch='1';break;
												case 1 : ch='2';break;
												case 2 : ch='3';break;
												case 3 : ch='A';break;
											}
											break; 
									case 1 : switch(C)
											{
												case 0 : ch='4';break;
												case 1 : ch='5';break;
												case 2 : ch='6';break;
												case 3 : ch='B';break;
											 }
									         break;
									case 2 : switch(C)
											{
												case 0 : ch='7';break;
												case 1 : ch='8';break;
												case 2 : ch='9';break;
												case 3 : ch='C';break;
											}
									        break;
									case 3 : switch(C)
											{
												case 0 : ch='*';break;
												case 1 : ch='0';break;
												case 2 : ch='#';break;
												case 3 : ch='D';break;
											}
											break;
									default: ch=0;break;
											
								}
								return ch;
					
					}