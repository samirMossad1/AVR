

#include "spi.h"


static void (*SPI_callBackPtr)(void)=NULL_PTR;




ISR(SPI_STC_vect)
{
	if(SPI_callBackPtr!=NULL_PTR)
		SPI_callBackPtr();

	SET_BIT(SPI_STATUS_REGISTER,SPI_INTERRUPT_FLAG);

}


bool SPI_deviceInit(const SPI_ConfigStruct * SPI_structPtr)
{

	if(SPI_structPtr == NULL_PTR ) 	return FALSE;

	/*CLEAR REGISTERS*/
	SPI_CONTROL_REGISTER=0x00;
	SPI_STATUS_REGISTER&=~(CLEAR_TRANSMISSION_SPEED_MASK);



	SPI_CONTROL_REGISTER|= ( (SPI_structPtr->SPI_INT)<<BIT_7)|
						   ( (SPI_structPtr->SPI_DEVICE_TYPE)<<BIT_4)|
						   ( (SPI_structPtr->SPI_CLCK_PHASE)<<BIT_2)|
						   ( (SPI_structPtr->SPI_CLCK_POLARITY)<<BIT_3)|
						   ( (SPI_structPtr->SPI_DATA_ORDER)<<BIT_5)|
						   ( (SPI_structPtr->SPI_FREQ_PRE));



	SPI_STATUS_REGISTER|=(SPI_structPtr->SPI_SPEED);


	SET_BIT(SPI_CONTROL_REGISTER,SPI_ENABLE);

	return TRUE;
}


uint8_t SPI_readByte()
{

	while(BIT_IS_CLEAR(SPI_STATUS_REGISTER,SPI_INTERRUPT_FLAG));

	return SPI_DATA_REGISTER;

}


void SPI_readString(char * str)
{
	uint16_t i=0;

do{
	str[i]=SPI_readByte();
	i++;

	} while(str[i-1] != '\0');


}


void SPI_sendByte(uint8_t data)
{

	while(BIT_IS_CLEAR(SPI_STATUS_REGISTER,SPI_INTERRUPT_FLAG));

	SPI_DATA_REGISTER=data;

}

void SPI_sendString(const char * str)
{
	uint16_t i=0;

	do
	{
		SPI_sendByte(str[i]);
		i++;

	}while(str[i-1] != '\0');


}


uint8_t SPI_readStatus()
{
	return SPI_STATUS_REGISTER>>7;
}


bool SPI_disable()
{

	RESET_BIT(SPI_CONTROL_REGISTER,SPI_ENABLE);

	return TRUE;
}

void SPI_setCallBack(void(*callBackPtr)(void))
{
	SPI_callBackPtr=callBackPtr;
}



bool SPI_disableInterrupt()
{
	RESET_BIT(SPI_CONTROL_REGISTER,SPI_INTERRUPT_ENABLE);
	return TRUE;
}
