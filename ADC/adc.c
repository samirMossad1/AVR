

#include "adc.h"


static void (*ADC_CallBackPtr)(void)=NULL_PTR;


ISR(ADC_vect)
{

	if(ADC_CallBackPtr != NULL_PTR)
		ADC_CallBackPtr();

	SET_BIT(ADC_CONTROL_STATUS_REGISTER,ADC_CONVERISON_FLAG);		/*CLEAR THE FLAG*/

}




bool ADC_init(const ADC_ConfigStruct* ADC_structPtr)
{

	if(ADC_structPtr == NULL_PTR) return FALSE;








	return TRUE;
}




uint16_t ADC_readChannel(const ADC_CHANNEL ADC_CHANNEL)
{

	CLEAR_N_BITS_THEN_OR(ADC_MULTIPLEXER_SEL_REGISTER,ADC_MUX_SELECT_CLEAR,ADC_CHANNEL,0X0);

	SET_BIT(ADC_CONTROL_STATUS_REGISTER,ADC_START_CONVERSION);

	while(BIT_IS_CLEAR(ADC_CONTROL_STATUS_REGISTER,ADC_CONVERISON_FLAG)); /*POLLING*/

	SET_BIT(ADC_CONTROL_STATUS_REGISTER,ADC_CONVERISON_FLAG);		/*CLEAR THE FLAG*/

	return  ADC_DATA_REGISTER;

}



void ADC_readChannelInterrupt(const ADC_CHANNEL ADC_CHANNEL,void(*callBackPtr)(void))  /*Use this conversion function in case of _INTERRUPTS*/
{

	if(callBackPtr == NULL_PTR) return;

	ADC_CallBackPtr=callBackPtr;

	CLEAR_N_BITS_THEN_OR(ADC_MULTIPLEXER_SEL_REGISTER,ADC_MUX_SELECT_CLEAR,ADC_CHANNEL,0X0);

	SET_BIT(ADC_CONTROL_STATUS_REGISTER,ADC_START_CONVERSION);

}


bool ADC_disable()
{
	RESET_BIT(ADC_CONTROL_STATUS_REGISTER,BIT_7);
	return TRUE;
}




