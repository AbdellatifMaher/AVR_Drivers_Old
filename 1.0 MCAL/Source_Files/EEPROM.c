/*
 * EEPROM.c
 *
 * Created: 7/1/2020 1:58:41 PM
 *  Author: 8
 */ 

 #include <EEPROM.h>
 #include "uc_Configuration.h"
 
 
 void EEPROM_WRITE(uint16_t addr,uint8_t data)
 {
	 while(((EECR->allRegister) & (1<<EEWE) == 1)   &&  ((SPMCR->allRegister) & (1<<SPMEN) == 1) )
	 {
		 
	 }
	 EEARH->allRegister = addr>>8;
	 EEARL->allRegister = addr;
	 EEDR->allRegister =data;
	 // EECR->allRegister |= (1<<EEMWE);
	 EECR->bits.b2= 1;
	 // EECR->allRegister |= (1<<EEWE);
	 EECR->bits.b1=1;
 }
 
 uint8_t EEPROM_READ(uint8_t addr)
 {
	 while( EECR->allRegister & (1<<EEWE))
	 {
		 
	 }
	 EEARH->allRegister = addr>>8;
	 EEARL->allRegister = addr ;
	 EECR->allRegister |= (1<<EERE);
	 return EEDR->allRegister ;
 }