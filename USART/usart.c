

#include "usart.h"


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



bool USART_disable()
{
	USART_CONTROL_STATUS_B_REGISTER &= ~(USART_DISABLE_MASK);
	return TRUE;
}
