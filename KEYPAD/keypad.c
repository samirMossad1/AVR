

#include "keypad.h"
#include "gpio.h"


bool KEYPAD_init(const KEYPAD_configStruct* KEYPAD_configPtr)
{

	if(KEYPAD_configPtr == NULL_PTR)
			return FALSE;

	uint8_t counter_t;
	GPIO_pinConfigStruct GPIO_PIN;

	for(counter_t=0;counter_t<KEYPAD_configPtr->KEYPAD_noOfRows;counter_t++)
	{

		GPIO_PIN->PORT=(*((KEYPAD_configPtr->KEYPAD_rowPORTS)+counter_t));
		GPIO_PIN->PIN=(*((KEYPAD_configPtr->KEYPAD_rowPins)+counter_t));
		GPIO_PIN->PIN_TYPE=_INPUT;

		GPIO_pinInit(&GPIO_PIN);
		GPIO_pinPullUpInit(GPIO_PIN->PORT,GPIO_PIN->PIN);

	}


	for(counter_t=0;counter_t<KEYPAD_configPtr->KEYPAD_noOfColumns;counter_t++)
	{

		GPIO_PIN->PORT=(*((KEYPAD_configPtr->KEYPAD_columnPORTS)+counter_t));
		GPIO_PIN->PIN=(*((KEYPAD_configPtr->KEYPAD_columnPins)+counter_t));
		GPIO_PIN->PIN_TYPE=_INPUT;

		GPIO_pinInit(&GPIO_PIN);

	}


	return TRUE;
}
