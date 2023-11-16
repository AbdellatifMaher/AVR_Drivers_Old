/*
 * MICROCHIP_EEPROM.c
 *
 * Created: 7/1/2020 4:52:59 PM
 *  Author: 8
 */ 

#include "uc_Configuration.h"
#include "GPIO_ATmega32A.h"
#include "SPI.h"
#include "MICROCHIP_EEPROM.h"
#include <util/delay.h>


#define WREN_OPCODE		(0x06)
#define WRTIE_OPCODE	(0x02)
#define READ_OPCODE		(0x03)

#define DUMMY_DATA		(0x00)

static void SPI_CS_Control(vuint8_t State)
{
	switch(State)
	{
		case 0:
		DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,LOW);
		break;
		case 1:
		DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,HIGH);
		break;
		default:
		break;
	}
}

void EEPROM_Init(void)
{
	SPI_USED.EnableControl = SPI_Enable;
	SPI_USED.Mode = SPI_MASTER;
	/* 
	 * Note : if Used SPI Mode 3 or Mode 2 (CLK IDLE STATE = HIGH)
	 * in Some MicroControllers we must Explicitly State that The Default clk pin state is High 
	 * By Setting the pin to Output with a High Value 
	 */
	SPI_USED.ClockMode = SPI_CLKMode3;
	SPI_USED.DataOrder = SPI_MSB;
	SPI_USED.Freq = SPI_FCPU_BY_8;
	SPI_USED.InterruptState = SPI_InterruptDisable;
	/* Config CS Pin  to be in output mode to use it as CS */
	DIO_pinConfigure(CHIP_SELECT_PORT,CHIP_SELECT_PIN,OUTPUT);
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,HIGH);
	SPI_Init();
}

void EEPROM_WriteByte(vuint8_t Data , vuint16_t address)
{
	/* Select EEPROM By Applying 0 to CS */
	SPI_CS_Control(0);
	/* Write Latch Enable */
	SPI_ReadWrite_Blocking(WREN_OPCODE);
	/* Apply High to CS to Make Write Latch Enable Instruction Executed*/
	SPI_CS_Control(1);
	_delay_ms(50);
	/* Select EEPROM By Applying 0 to CS */
	SPI_CS_Control(0);
	SPI_ReadWrite_Blocking(WRTIE_OPCODE);
	SPI_ReadWrite_Blocking(address);
	SPI_ReadWrite_Blocking(Data);
	SPI_CS_Control(1);
}


vuint8_t EEPROM_ReadByte(vuint16_t address)
{
	
	vuint8_t ReadData = 0;
	SPI_CS_Control(0);
	SPI_ReadWrite_Blocking(READ_OPCODE);
	SPI_ReadWrite_Blocking(address);
	ReadData = SPI_ReadWrite_Blocking(DUMMY_DATA);
	SPI_CS_Control(1);
	return ReadData;
}