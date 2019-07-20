

#include "adc.h"


static volatile ADC_callBackPtr=NULL_PTR;




void ISR(ADC_vect)
{
	if(ADC_callBackPtr!=NULL_PTR)
		ADC_callBackPtr();
}




