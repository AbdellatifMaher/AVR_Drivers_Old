/*
 * I2C.h
 *
 * Created: 7/12/2020 10:48:57 AM
 *  Author: 8
 */ 


#ifndef I2C_H_
#define I2C_H_
	#include "uc_Configuration.h"

		#define  GENERAL_CALL (0x00)

		typedef enum {
			TWIE,
			TWEN=2,
			TWWC,
			TWSTO,
			TWSTA,
			TWEA,
			TWINT,
			}TWCR_REG;

		typedef enum {
			TWPS0,
			TWPS1,
			TWGCE=0,
			}I2C_REG;
		
		typedef enum {
			I2C_Disable,
			I2C_Enable_Slave_GCALL,
			I2C_Enable_Slave_NOGCALL,
			I2C_Enable_Master,
			}I2C_Mode;
		typedef enum {
				I2C_InterrDISABLE,
				I2C_InterrENABLE,
			}I2C_InterrMode;
		typedef enum {
			Prescaler_1_Normal,
			Prescaler_1_Fast,
			Prescaler_4_Normal,
			Prescaler_4_Fast,
			Prescaler_16_Normal,
			Prescaler_16_Fast,
			Prescaler_64_Normal,
			Prescaler_64_Fast,
		}I2C_Pre;
		typedef enum {
			 START_COND_CODE =(0x08),
			 RP_START_COND_CODE=(0x10),
			 SLAW_ACK_CODE=(0x18),
			 SLAW_NACK_CODE=(0x20),
			 SLAR_ACK_CODE=(0x40),
			 SLAR_NACK_CODE=(0x48),
			 DATABYTE_TX_ACK_CODE=(0x28),
			 DATABYTE_TX_NACK_CODE=(0x30),
			 DATABYTE_RX_ACK_CODE=(0x50),
			 DATABYTE_RX_NACK_CODE=(0x58),
			 ARBITRATION_LOST_CODE=(0x38),
			 WRITE_COLLISION_ERROR,
			 SLAVE_SLA_W_ACK_CODE=(0x60),
			 SLAVE_ARB_LOST_SLA_W_ACK_CODE=(0x68),
			 SLAVE_GC_ACK_CODE=(0x70),
			 SLAVE_ARB_LOST_GC_ACK_CODE=(0x78),
			 SLAVE_DATA_RX_ACK_CODE=(0x80),
			 SLAVE_DATA_RX_NACK_CODE=(0x88),
			 SLAVE_GC_DATA_RX_ACK_CODE=(0x90),
			 SLAVE_GC_DATA_RX_NACK_CODE=(0x98),
			 SLAVE_STOP_RP_RX_CODE=(0xA0),
			 SLAVE_SLA_R_ACK_CODE=(0xA8),
			 SLAVE_ARB_LOST_SLA_R_ACK_CODE=(0xB0),
			 SLAVE_DATA_TX_ACK_CODE=(0xB8),
			 SLAVE_DATA_TX_NACK_CODE=(0xC0),
			 SLAVE_LAST_DATA_TX_ACK_CODE=(0xC8),
			/*When a transfer is successful this is set to 0xFF. 
			There are no possible error codes that can take the value of 0xFF
			 even if the TWSR is masked wrong,
			 this is because the reserved bit 2 is zero and read only. */
			 NO_ERRORS=0xFF,
		}I2C_STATUS_CODES;
		
		
		typedef struct 
		{
			I2C_Mode             TWI_MODE;
			I2C_Pre              TWI_SCL_freq;
			I2C_InterrMode       TWI_Interrupt;
			vuint8_t             SlaveAddress;
			vuint8_t             InterrCounter;
			vuint8_t             InterrRxBuff[20];
			vuint8_t             SlaveTxCounter;
			vuint8_t             SlaveTxBuff[20];
			I2C_STATUS_CODES     TWI_ERRORS;
			/* Make The Pointer points to a Function you wish to be Called by TWI Interrupt */
			void (*TWI_InterruptCall) (void);
			
		}I2C_ConfigurationStruct;
		
		    extern I2C_ConfigurationStruct I2C0;
			
			void I2C_Init(void);
			vuint8_t I2C_WriteData_Master(vuint8_t SAddress,vuint8_t RegAddress,vuint8_t *Data,vuint8_t num);
			vuint8_t I2C_ReadData_ACK_Mastr(vuint8_t SAddress,vuint8_t RegAddress);
			vuint8_t I2C_ReadData_NACK_Master(vuint8_t SAddress,vuint8_t RegAddress);
			void I2C_WriteData_Master_Interrupt(vuint8_t SAddress,vuint8_t *Data,vuint8_t num);
			void I2C_ReadData_Master_Interrupt(vuint8_t SAddress,vuint8_t RegAddress,vuint8_t num);
			vuint8_t I2C_Slave_Interrupt(void);
	
	



#endif /* I2C_H_ */