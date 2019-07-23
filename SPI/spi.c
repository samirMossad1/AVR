

#include "spi.h"


static void (*SPI_callBackPtr)(void)=NULL_PTR;















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
