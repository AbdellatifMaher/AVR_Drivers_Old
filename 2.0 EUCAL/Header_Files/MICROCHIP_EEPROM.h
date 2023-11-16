/*
 * MICROCHIP_EEPROM.h
 *
 * Created: 7/1/2020 4:48:20 PM
 *  Author: Abdellatif
 */ 


#ifndef MICROCHIP_EEPROM_H_
#define MICROCHIP_EEPROM_H_

	#include "uc_Configuration.h"
	#include "GPIO_ATmega32A.h"

	#define CHIP_SELECT_PORT		DIOB
	#define CHIP_SELECT_PIN			PIN0
	#define SPI_USED				SPI0
	
	void EEPROM_Init(void);
	void EEPROM_WriteByte(vuint8_t Data , vuint16_t  address);
	vuint8_t  EEPROM_ReadByte(vuint16_t  address);





#endif /* MICROCHIP_EEPROM_H_ */