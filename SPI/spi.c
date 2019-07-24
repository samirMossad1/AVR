

#include "spi.h"


static void (*SPI_callBackPtr)(void)=NULL_PTR;











ISR(SPI_STC_vect)
{
	if(SPI_callBackPtr!=NULL_PTR)
		SPI_callBackPtr();

	SET_BIT(SPI_STATUS_REGISTER,SPI_INTERRUPT_FLAG);

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
