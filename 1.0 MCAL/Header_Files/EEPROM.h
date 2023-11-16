/*
 * EEPROM.h
 *
 * Created: 7/1/2020 1:53:19 PM
 *  Author: 8
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

 	#include "uc_Configuration.h"
 	
 	

 	#define EERIE   PIN3
 	#define EEMWE   PIN2
 	#define EEWE    PIN1
 	#define EERE    PIN0
 	#define SPMEN   PIN0

 	void EEPROM_WRITE(uint16_t addr,uint8_t data);
 	uint8_t EEPROM_READ(uint8_t addr);




#endif /* EEPROM_H_ */