

#include "keypad.h"
#include "gpio.h"


static uint8_t (*CallBack_ptr)(uint8_t);

bool KEYPAD_init(const KEYPAD_configStruct* KEYPAD_configPtr)
{

	if(KEYPAD_configPtr == NULL_PTR)
		return FALSE;

	uint8_t counter_t;
	GPIO_pinConfigStruct GPIO_PIN;

	for(counter_t=0;counter_t<KEYPAD_configPtr->KEYPAD_noOfRows;counter_t++)
	{

		GPIO_PIN.PORT=(*((KEYPAD_configPtr->KEYPAD_rowPORTS)+counter_t));
		GPIO_PIN.PIN=(*((KEYPAD_configPtr->KEYPAD_rowPins)+counter_t));
		GPIO_PIN.PIN_TYPE=_INPUT;

		GPIO_pinInit(&GPIO_PIN);
		GPIO_pinPullUpInit(GPIO_PIN.PORT,GPIO_PIN.PIN);

	}


	for(counter_t=0;counter_t<KEYPAD_configPtr->KEYPAD_noOfColumns;counter_t++)
	{

		GPIO_PIN.PORT=(*((KEYPAD_configPtr->KEYPAD_columnPORTS)+counter_t));
		GPIO_PIN.PIN=(*((KEYPAD_configPtr->KEYPAD_columnPins)+counter_t));
		GPIO_PIN.PIN_TYPE=_INPUT;

		GPIO_pinInit(&GPIO_PIN);

	}


	return TRUE;
}



uint8_t KEYPAD_getPressedKey(const KEYPAD_configStruct* KEYPAD_configPtr)
{


	if(KEYPAD_configPtr == NULL_PTR)
		return FALSE;

	uint8_t counterCols_t,counterRows_t;

	GPIO_pinConfigStruct GPIO_pin;


	for(counterCols_t=0;counterCols_t<KEYPAD_configPtr->KEYPAD_noOfColumns;counterCols_t++)
	{

		GPIO_pin.PORT=(*((KEYPAD_configPtr->KEYPAD_rowPORTS)+counterCols_t));
		GPIO_pin.PIN=(*((KEYPAD_configPtr->KEYPAD_rowPins)+counterCols_t));
		GPIO_pin.PIN_TYPE=_OUTPUT;


		GPIO_pinInit(&GPIO_pin);
		GPIO_writePin(GPIO_pin.PORT,GPIO_pin.PIN,_LOW_LEVEL);


		for(counterRows_t=0;counterRows_t<KEYPAD_configPtr->KEYPAD_noOfRows;counterRows_t++)
		{

			if(!GPIO_readPin((*((KEYPAD_configPtr->KEYPAD_rowPORTS)+counterRows_t)),
					(*((KEYPAD_configPtr->KEYPAD_rowPins)+counterRows_t))))
			{

				return	CallBack_ptr((counterRows_t*KEYPAD_configPtr->KEYPAD_noOfColumns)*counterCols_t+1);

			}

		}


		GPIO_pin.PIN_TYPE=_INPUT;
		GPIO_pinInit(&GPIO_pin);

	}


return 0x00;
}
