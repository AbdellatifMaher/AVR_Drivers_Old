/*
 * I2C.c
 *
 * Created: 7/12/2020 10:51:43 AM
 *  Author: 8
 */
#include "I2C.h"
#include "uc_Configuration.h"

                     #define TWI_VECTOR	  _VECTOR(19)

I2C_ConfigurationStruct I2C0={0, .TWI_ERRORS=NO_ERRORS,.TWI_InterruptCall = NULL};
	
ISR(TWI_VECTOR)
{
	if(I2C0.TWI_InterruptCall !=NULL)
	{
		I2C0.TWI_InterruptCall();
	}
}
	
/*========================================****Important Function To Devoloper **********==================================*/ 	
static void I2C_SendStartCond_Blocking(void)
{
	/*save value to TWEN & TWIE and clear other bits*/ 
	TWCR->allRegister&=0x07;
	/* to clear flag and set start condition*/
	SETBIT(TWCR->allRegister,TWINT);
	SETBIT(TWCR->allRegister,TWSTA);
	while ((TWCR->allRegister &(1<<TWINT)) == 0)
	{
		/* wait start condition to be transmited */
	}
}
static void I2C_SendStartCond_NonBlocking(void)
{
	/*save value to TWEN & TWIE and clear other bits*/
	TWCR->allRegister&=0x07;
	/* to clear flag and set start condition*/
	SETBIT(TWCR->allRegister,TWINT);
	SETBIT(TWCR->allRegister,TWSTA);
}
static void I2C_SendStopCond_Blocking(void)
{
	/*save value to TWEN & TWIE and clear other bits*/
	TWCR->allRegister&=0x07;
	/* to clear flag and set stop condition*/
	SETBIT(TWCR->allRegister,TWINT);
	SETBIT(TWCR->allRegister,TWSTO);
	while ((TWCR->allRegister &(1<<TWINT)) == 0)
	{
		/* wait stop condition to be transmited */
	}
}
static void I2C_SendStopCond_NonBlocking(void)
{
	/*save value to TWEN & TWIE and clear other bits*/
	TWCR->allRegister&=0x07;
	/* to clear flag and set stop condition*/
	SETBIT(TWCR->allRegister,TWINT);
	SETBIT(TWCR->allRegister,TWSTO);
}
static void I2C_WriteData_Blocking(vuint8_t data)
{
	TWCR->allRegister&=0x07;
	SETBIT(TWCR->allRegister,TWINT);
	TWDR->allRegister= data;
	/*wait data to be Tx */
	while ((TWCR->allRegister &(1<<TWINT)) == 0){};
}
static void I2C_WriteData_NonBlocking(vuint8_t data)
{
	TWCR->allRegister&=0x07;
	SETBIT(TWCR->allRegister,TWINT);
	TWDR->allRegister= data;
}
static vuint8_t I2C_ReadData_ACK_Blocking(void)
{ 	
	TWCR->allRegister&=0x07;
	SETBIT(TWCR->allRegister,TWINT);
	SETBIT(TWCR->allRegister,TWEA);
	/*wait data to be Rx */
	while ((TWCR->allRegister &(1<<TWINT)) == 0){};
	return TWDR->allRegister ;
}
static vuint8_t I2C_ReadData_NACK_Blocking(void)
{
		TWCR->allRegister=0x07;
		SETBIT(TWCR->allRegister,TWINT);
		/*wait data to be Rx */
		while ((TWCR->allRegister &(1<<TWINT)) == 0){};
		return TWDR->allRegister ;
}
static vuint8_t I2C_ReadData_ACK_NonBlocking(void)
{
	TWCR->allRegister&=0x07;
	SETBIT(TWCR->allRegister,TWINT);
	SETBIT(TWCR->allRegister,TWEA);
	return TWDR->allRegister ;
}
static vuint8_t I2C_ReadData_NACK_NonBlocking(void)
{
	TWCR->allRegister=0x07;
	SETBIT(TWCR->allRegister,TWINT);
	return TWDR->allRegister ;
}
static vuint8_t I2C_GetStatus(void)
{
	return ((TWSR->allRegister) & 0xF8);
}
/* ======================================================================================================================== */

void I2C_Init(void){
	
	switch(I2C0.TWI_MODE)
	{
		case I2C_Disable: CLEARBIT(TWCR->allRegister,TWEN);break;
		case I2C_Enable_Master : SETBIT(TWCR->allRegister,TWEN);break;
		case I2C_Enable_Slave_NOGCALL : TWAR->allRegister=I2C0.SlaveAddress<<1; SETBIT(TWCR->allRegister,TWEN);break;
		case I2C_Enable_Slave_GCALL : TWAR->allRegister=I2C0.SlaveAddress<<1; SETBIT(TWCR->allRegister,TWEN);SETBIT(TWAR->allRegister,TWGCE);break;
		default:break;
	}
	switch(I2C0.TWI_SCL_freq)
	{
		case  Prescaler_1_Normal : TWBR->allRegister = (((F_CPU)/(2*100000))-8) /1 ;break;
		case  Prescaler_1_Fast   : TWBR->allRegister = (((F_CPU)/(2*400000))-8) /1 ;break;
		case  Prescaler_4_Normal : TWBR->allRegister = (((F_CPU)/(2*100000))-8) /4 ;break;
		case  Prescaler_4_Fast   : TWBR->allRegister = (((F_CPU)/(2*400000))-8) /4 ;break;
		case  Prescaler_16_Normal: TWBR->allRegister = (((F_CPU)/(2*100000))-8) /16 ;break;
		case  Prescaler_16_Fast  : TWBR->allRegister = (((F_CPU)/(2*400000))-8) /16 ;break;	
		case  Prescaler_64_Normal: TWBR->allRegister = (((F_CPU)/(2*100000))-8) /64 ;break;
		case  Prescaler_64_Fast  : TWBR->allRegister = (((F_CPU)/(2*400000))-8) /64 ;break;	
		default:break;
	}
	switch(I2C0.TWI_Interrupt)
	{
		case I2C_InterrDISABLE : CLEARBIT(TWCR->allRegister,TWIE);break;
		case I2C_InterrENABLE  : SETBIT(TWCR->allRegister,TWIE);break;
		default:break;
			}
	TWSR->allRegister&= 0x07;
	
} 

 vuint8_t I2C_WriteData_Master(vuint8_t SAddress,vuint8_t RegAddress,vuint8_t *Data,vuint8_t num)
{
	//start Cond
	I2C_SendStartCond_Blocking();
	if(I2C_GetStatus() != START_COND_CODE)
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
		       I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
			   return 0;
		}
		else
		{
				 I2C0.TWI_ERRORS= I2C_GetStatus() ;
				 return 0;
		}
	}
	//SLA + W
	I2C_WriteData_Blocking((SAddress <<1) | 0x00);
	if( I2C_GetStatus() != SLAW_ACK_CODE )
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
			return 0;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
			return 0;
		}
	}
	//Register Address
	I2C_WriteData_Blocking(RegAddress);
	if(I2C_GetStatus() != DATABYTE_TX_ACK_CODE)
	{
			if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
			{
				I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
				return 0;
			}
			else
			{
				I2C0.TWI_ERRORS= I2C_GetStatus() ;
				return 0;
			}
		}
	//Send Data
	for(vuint8_t i=0;i<num;i++)
	{
	I2C_WriteData_Blocking(Data[i]);
	if(I2C_GetStatus() != DATABYTE_TX_ACK_CODE || I2C_GetStatus() != DATABYTE_TX_NACK_CODE )
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
			return 0;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
			return 0;
		}
	}
	}
	//Stop Cond
	I2C_SendStopCond_Blocking();
	return 1;
}
vuint8_t I2C_ReadData_ACK_Mastr(vuint8_t SAddress,vuint8_t RegAddress)
{
		vuint8_t DataRx=0;
		//start Cond
		I2C_SendStartCond_Blocking();
		if(I2C_GetStatus() != START_COND_CODE)
		{
			//ERROR
			if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
			{
				I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
			}
			else
			{
				I2C0.TWI_ERRORS= I2C_GetStatus() ;
			}
		}
		//SLA + W
		I2C_WriteData_Blocking((SAddress <<1) | 0x00);
		if(I2C_GetStatus() != SLAW_ACK_CODE || I2C_GetStatus() != SLAW_NACK_CODE )
		{
			//ERROR
			if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
			{
				I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
			}
			else
			{
				I2C0.TWI_ERRORS= I2C_GetStatus() ;
			}
		}
		//Register Address
		I2C_WriteData_Blocking(RegAddress);
		if(I2C_GetStatus() != DATABYTE_TX_ACK_CODE )
			{
				//ERROR
				if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
				{
					I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
				}
				else
				{
					I2C0.TWI_ERRORS= I2C_GetStatus() ;
				}
			}
		//send RP START COND
		I2C_SendStartCond_Blocking();
		if(I2C_GetStatus() != RP_START_COND_CODE)
		{
			//ERROR
			if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
			{
				I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
			}
			else
			{
				I2C0.TWI_ERRORS= I2C_GetStatus() ;
			}
		}
	  //Send SLA+R
	  I2C_WriteData_Blocking((SAddress <<1) | 0x01);
	  if(I2C_GetStatus() != SLAR_ACK_CODE  )
	  {
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	  }
	  DataRx = I2C_ReadData_ACK_Blocking();
	  if(I2C_GetStatus() != DATABYTE_RX_ACK_CODE )
	  {
		  //ERROR 
		  if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		  {
			  I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		  }
		  else
		  {
			  I2C0.TWI_ERRORS= I2C_GetStatus() ;
		  }
	  }
	  
	//Stop Cond
	I2C_SendStopCond_Blocking();
	return DataRx ;
}
vuint8_t I2C_ReadData_NACK_Master(vuint8_t SAddress,vuint8_t RegAddress)
{
	vuint8_t DataRx=0;
	//start Cond
	I2C_SendStartCond_Blocking();
	if(I2C_GetStatus() != START_COND_CODE)
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	}
	//SLA + W
	I2C_WriteData_Blocking((SAddress <<1) | 0x00);
	if(I2C_GetStatus() != SLAW_ACK_CODE || I2C_GetStatus() != SLAW_NACK_CODE )
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	}
	//Register Address
	I2C_WriteData_Blocking(RegAddress);
	if(I2C_GetStatus() != DATABYTE_TX_ACK_CODE )
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	}
	//send RP START COND
	I2C_SendStartCond_Blocking();
	if(I2C_GetStatus() != RP_START_COND_CODE)
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	}
	//Send SLA+R
	I2C_WriteData_Blocking((SAddress <<1) | 0x01);
	if(I2C_GetStatus() != SLAR_ACK_CODE  )
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	}
	DataRx = I2C_ReadData_NACK_Blocking();
	if(I2C_GetStatus() != DATABYTE_RX_NACK_CODE )
	{
		//ERROR
		if( I2C_GetStatus() == ARBITRATION_LOST_CODE)
		{
			I2C0.TWI_ERRORS= ARBITRATION_LOST_CODE;
		}
		else
		{
			I2C0.TWI_ERRORS= I2C_GetStatus() ;
		}
	}
	
	//Stop Cond
	I2C_SendStopCond_Blocking();
	return DataRx ;
}
void I2C_WriteData_Master_Interrupt(vuint8_t SAddress,vuint8_t *Data,vuint8_t num)
{
	/* You Must Send Start cond befor this function */
	switch(I2C_GetStatus())
	{
		case START_COND_CODE : I2C_WriteData_NonBlocking((SAddress <<1) | 0x00);break;
		case SLAW_ACK_CODE : I2C_WriteData_NonBlocking(Data[I2C0.InterrCounter++]);break;
		case DATABYTE_TX_ACK_CODE: if(I2C0.InterrCounter < num) 
									{
										I2C_WriteData_NonBlocking(Data[I2C0.InterrCounter++]);break;
									}
									else
									{
										I2C0.InterrCounter =0;
										I2C_SendStopCond_NonBlocking();
									}
									break;
		case SLAW_NACK_CODE        : 
		case DATABYTE_TX_NACK_CODE : 
		case ARBITRATION_LOST_CODE : I2C0.TWI_ERRORS= I2C_GetStatus(); I2C0.InterrCounter =0;
									 I2C_SendStopCond_NonBlocking(); break; 
		default                    :break;	
	}
}
void I2C_ReadData_Master_Interrupt(vuint8_t SAddress,vuint8_t RegAddress,vuint8_t num)
{
	/* You Must Send Start cond befor this function */
	/* countData to know the last data recived */
	uint8_t countData=0;
	switch(I2C_GetStatus())
	{
		case START_COND_CODE : I2C_WriteData_NonBlocking((SAddress <<1) | 0x00);break;
		case SLAW_ACK_CODE :  I2C_WriteData_NonBlocking(RegAddress);break;
		case DATABYTE_TX_ACK_CODE: I2C_SendStartCond_NonBlocking();break;
		case RP_START_COND_CODE : I2C_WriteData_NonBlocking((SAddress <<1) | 0x01);break;
		case SLAR_ACK_CODE :  if(countData ==(num-1)){
			                    I2C0.InterrRxBuff[countData]=I2C_ReadData_NACK_NonBlocking();
								countData++;
							    }
							 else
							 {
								 I2C0.InterrRxBuff[countData]=I2C_ReadData_ACK_NonBlocking();
								 countData++;
							 }
							 break;
		case DATABYTE_RX_ACK_CODE :    if(countData ==(num-1)){
											
											I2C0.InterrRxBuff[countData]=I2C_ReadData_NACK_NonBlocking();
											countData++;
		                               } 
									   else if(countData == num)
									   {
										   I2C_SendStopCond_NonBlocking();
									   }
									   else
									   {
										   I2C0.InterrRxBuff[countData]=I2C_ReadData_ACK_NonBlocking();
										   	countData++;
									   }
									   break;
		case SLAR_NACK_CODE        : 
		case SLAW_NACK_CODE        :
		case DATABYTE_TX_NACK_CODE :
		case DATABYTE_RX_NACK_CODE : 
		case ARBITRATION_LOST_CODE :I2C0.TWI_ERRORS= I2C_GetStatus(); I2C0.InterrCounter =0;
		                             I2C_SendStopCond_NonBlocking(); break;
		default:break;
	}
}

vuint8_t I2C_Slave_Interrupt(void)
{
	vuint8_t R=0;
	switch(I2C_GetStatus())
	{
		case SLAVE_GC_ACK_CODE      :
		case SLAVE_SLA_W_ACK_CODE   : SETBIT(TWCR->allRegister,TWINT);SETBIT(TWCR->allRegister,TWEA); SETBIT(TWCR->allRegister,TWEN);break;
		case SLAVE_GC_DATA_RX_ACK_CODE :
		case SLAVE_DATA_RX_ACK_CODE :  R=TWDR->allRegister; TWCR->allRegister&=0x07; SETBIT(TWCR->allRegister,TWINT); return R;break;
		case SLAVE_SLA_R_ACK_CODE   : TWCR->allRegister&=0x07; TWDR->allRegister=I2C0.SlaveTxBuff[I2C0.SlaveTxCounter++]; SETBIT(TWCR->allRegister,TWINT);break;
		case SLAVE_DATA_TX_ACK_CODE : if(I2C0.SlaveTxCounter == 19)
											{
												TWDR->allRegister=I2C0.SlaveTxBuff[I2C0.SlaveTxCounter++];
												CLEARBIT(TWCR->allRegister,TWEA);
												SETBIT(TWCR->allRegister,TWINT);
												I2C0.SlaveTxCounter=0;
											}
											else
											{
												TWDR->allRegister=I2C0.SlaveTxBuff[I2C0.SlaveTxCounter++];
												SETBIT(TWCR->allRegister,TWINT);
											}
											break;									
		case SLAVE_DATA_TX_NACK_CODE       :
		case SLAVE_GC_DATA_RX_NACK_CODE    :
		case SLAVE_STOP_RP_RX_CODE         :
		case SLAVE_LAST_DATA_TX_ACK_CODE   : 
		case SLAVE_ARB_LOST_SLA_W_ACK_CODE :
		case SLAVE_ARB_LOST_GC_ACK_CODE    :
		case SLAVE_ARB_LOST_SLA_R_ACK_CODE : I2C0.TWI_ERRORS=I2C_GetStatus();TWCR->allRegister&=0x07; SETBIT(TWCR->allRegister,TWINT);break;
		default                            :break;					
	}
	return R;
}