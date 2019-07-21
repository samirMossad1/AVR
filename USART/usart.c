

#include "usart.h"

#define BAUD_PRESCALAR(FREQ,N,BR)     (  (  (FREQ)/(N *BR)  ) -1)


static void(*USART_callBackPtrs[3])(void)=
{
		NULL_PTR,		/*USART_RECEIVE*/
		NULL_PTR,		/*USART_TRANSMIT*/
		NULL_PTR		/*USART_DATA_EMPTY*/
};



ISR(USART_RXC_vect)
{
	if(USART_callBackPtrs[0] != NULL_PTR)
		USART_callBackPtrs[0]();

	SET_BIT(USART_CONTROL_STATUS_A_REGISTER, USART_RECEIVE_COMPLETE_FLAG);

}


ISR(USART_TXC_vect)
{
	if(USART_callBackPtrs[1] != NULL_PTR)
		USART_callBackPtrs[1]();

}

ISR(USART_UDRE_vect)
{
	if(USART_callBackPtrs[2] != NULL_PTR)
		USART_callBackPtrs[2]();
}




bool USART_init(const USART_ConfigStruct* USART_structPtr)
{
	uint16_t baud_rate_number;
	uint8_t baud_rate_constant_factor;

	if(USART_structPtr == NULL_PTR) return FALSE;


	 /*Clear Registers*/

	USART_CONTROL_STATUS_A_REGISTER&=USART_CONTROL_REG_A_CLEAR;
	USART_CONTROL_STATUS_B_REGISTER=0X00;
	USART_CONTROL_STATUS_C_REGISTER=0X00;





	SET_BIT(USART_CONTROL_STATUS_B_REGISTER,USART_TRANSMITER_ENABLE);
	SET_BIT(USART_CONTROL_STATUS_B_REGISTER,USART_RECEIVER_ENABLE);
	USART_CONTROL_STATUS_B_REGISTER|=((USART_structPtr->USART_CS)&0x04);

	USART_CONTROL_STATUS_B_REGISTER&=~(1<<2);

	SET_BIT(USART_CONTROL_STATUS_C_REGISTER,USART_REGISTER_SELECT);

	USART_CONTROL_STATUS_C_REGISTER |= ((USART_structPtr->USART_MODE) << BIT_6) |
									   ((USART_structPtr->USART_PARITY)<< BIT_4)|
									   ((USART_structPtr->USART_STOP) << BIT_3) |
									   (((USART_structPtr->USART_CS)&0x03)<<BIT_1);



	if(USART_structPtr->USART_MODE == _ASYNCHRONOUS)
	{

		USART_CONTROL_STATUS_A_REGISTER|=((USART_structPtr->USART_SPEED)<< BIT_1);

		if(USART_structPtr->USART_SPEED == _NORMAL_SPEED ) baud_rate_constant_factor=16;
		else											   baud_rate_constant_factor=8;

	}
	else
	{
		USART_CONTROL_STATUS_C_REGISTER|=(USART_structPtr->USART_CLOCK);
		baud_rate_constant_factor=0x02;
	}


	RESET_BIT(USART_CONTROL_STATUS_C_REGISTER,USART_REGISTER_SELECT);


	/*BAUD RATE*/
	baud_rate_number=BAUD_PRESCALAR(USART_structPtr->Freq_CPU,baud_rate_constant_factor,USART_structPtr->USART_baudRate);

	USART_BAUD_RATE_HIGH_REGISTER=baud_rate_number>>BIT_8;
	USART_BAUD_RATE_LOW_REGISTER=baud_rate_number;


	/*INTERRUPTS*/

	USART_CONTROL_STATUS_B_REGISTER|=((USART_structPtr->USART_REC_INT)<<BIT_7)|
									 ((USART_structPtr->USART_TRANS_INT)<<BIT_6)|
									 ((USART_structPtr->USART_DATA_REG_INT)<<BIT_5);






return TRUE;
}





uint8_t USART_receiveByte()
{

  while(BIT_IS_CLEAR(USART_CONTROL_STATUS_A_REGISTER,USART_RECEIVE_COMPLETE_FLAG));

  return USART_DATA_REGISTER ;

}



void USART_sendByte(const uint8_t trans_data)
{

	while(BIT_IS_CLEAR(USART_CONTROL_STATUS_A_REGISTER,USART_DATA_REGISTER_EMPTY_FLAG));

	USART_DATA_REGISTER = trans_data;
}





void USART_receiveString(char * string)
{
	uint16_t i=0;

	do{

		string[i]=USART_receiveByte();
	    i++;

	}while(string[i-1] != '#');


	string[i-1] = '\0';

}





void USART_sendString(const char* string)
{

	uint16_t i=0;

	while(string[i] != '\0')
	{

		USART_sendByte(string[i]);

		i++;

	}


 /*We will mark the end of the string with '#' and this character will be checked upon in the receive string function*/

}


uint8_t USART_readDataReg()
{
	return USART_DATA_REGISTER ;
}

void USART_setCallBack(const USART_INTERRUPT_TYPE INTERRUPT_TYPE,void(*callBackPtr)(void))
{


	switch(INTERRUPT_TYPE)
	{

	case _TRANSMITTER_INTERRUPT :	USART_callBackPtrs[1]=callBackPtr;
									break;

	case _RECEIVER_INTERRUPT :		USART_callBackPtrs[0]=callBackPtr;
									break;

	case _DATA_REG_INTERRUPT :		USART_callBackPtrs[2]=callBackPtr;
									break;

	}


}

bool USART_disableInterrupt(const USART_INTERRUPT_TYPE INTERRUPT_TYPE)
{

	switch(INTERRUPT_TYPE)
	{

	case _TRANSMITTER_INTERRUPT :	RESET_BIT(USART_CONTROL_STATUS_B_REGISTER,BIT_6);
									break;

	case _RECEIVER_INTERRUPT :		RESET_BIT(USART_CONTROL_STATUS_B_REGISTER,BIT_7);
									break;

	case _DATA_REG_INTERRUPT :		RESET_BIT(USART_CONTROL_STATUS_B_REGISTER,BIT_5);
									break;

	}

	return TRUE;

}



bool USART_disable()
{
	USART_CONTROL_STATUS_B_REGISTER &= ~(USART_DISABLE_MASK);
	return TRUE;
}
