/*
 * GPIO_ATmega32A.h
 *
 * Created: 6/9/2020 4:07:52 PM
 *  Author: Abdellatif
 */ 


#ifndef GPIO_ATMEGA32A_H_
#define GPIO_ATMEGA32A_H_

  #include "uc_Configuration.h"
  #include "MACROS.h"
  #include "StdTypes.h"

/******************************************* Defines for Port  **************************************/

		 #define DIOA ((DIO *)(0x19+IO_OFFSET))
		 #define DIOB ((DIO *)(0x16+IO_OFFSET))
		 #define DIOC ((DIO *)(0x13+IO_OFFSET))
		 #define DIOD ((DIO *)(0x10+IO_OFFSET))
		 
		 
/******************************************* User Types For AVR Input/Output MCU **************************************/

  typedef enum
   {
	INPUT_FLOAT,
	INPUT_PULLUP,
	OUTPUT,
   }pinMode; 
/******************************************* IO Functions Prototype ***************************************************/

	void	DIO_pinConfigure(
								DIO * Dio,
								pinNumber pinNum,
								pinMode Mode);
	
	void	DIO_pinWrite(
								DIO * Dio,
								pinNumber pinNum,
								digitalState State);
	
	digitalState DIO_pinRead(
								DIO * Dio,
								pinNumber pinNum);

	void	DIO_portConfigure(
								DIO * Dio,
								vuint8_t ConfigByte);

	void	DIO_portWrite(
								DIO * Dio,
								vuint8_t Data);

	vuint8_t DIO_portRead(DIO * Dio); 
 
 
#endif /* GPIO_ATMEGA32A_H_ */