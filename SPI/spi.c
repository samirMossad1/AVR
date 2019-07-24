

#include "spi.h"


static void (*SPI_callBackPtr)(void)=NULL_PTR;

static void SPI_masterGPIOInit(void);
static void SPI_slaveGPIOInit(void);



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
			       ( (SPI_structPtr->SPI_CLCK_PHASE)<<BIT_2)|
			       ( (SPI_structPtr->SPI_CLCK_POLARITY)<<BIT_3)|
	      		       ( (SPI_structPtr->SPI_DATA_ORDER)<<BIT_5)|
			       ( (SPI_structPtr->SPI_FREQ_PRE));


	if(SPI_structPtr->SPI_DEVICE_TYPE == _SPI_MASTER)
	{
	SET_BIT(SPI_CONTROL_REGISTER,SPI_MASTER);
		SPI_masterGPIOInit();
	}
	else
	{
		RESET_BIT(SPI_CONTROL_REGISTER,SPI_MASTER);
		SPI_slaveGPIOInit();
	}

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

do
{
	str[i]=SPI_readByte();

	i++;

}while(str[i-1]!='#');

	str[i-1]='\0';

}


void SPI_sendByte(uint8_t data)
{


	SPI_DATA_REGISTER=data;

	while(BIT_IS_CLEAR(SPI_STATUS_REGISTER,SPI_INTERRUPT_FLAG));

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



bool SPI_checkCollision()
{

	if(BIT_IS_SET(SPI_STATUS_REGISTER,SPI_WRITE_COLLISION_FLAG))
		return TRUE;
	else
		return FALSE;

}


bool SPI_disableInterrupt()
{
	RESET_BIT(SPI_CONTROL_REGISTER,SPI_INTERRUPT_ENABLE);
	return TRUE;
}

static void SPI_masterGPIOInit(void)
{

	SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_SLAVE_SELECT_PIN);
	SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_MASTER_OUT_SLAVE_IN);
	SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_MASTER_CLOCK);
	RESET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_MASTER_IN_SLAVE_OUT);

}

static void SPI_slaveGPIOInit(void)
{


	RESET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_SLAVE_SELECT_PIN);
	RESET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_MASTER_OUT_SLAVE_IN);
	RESET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_MASTER_CLOCK);
	SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,SPI_MASTER_IN_SLAVE_OUT);

}


