

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "micro_config.h"
#include "std_types.h"
#include "macros.h"




typedef struct
{

	GPIO_PIN * KEYPAD_rowPins;
	GPIO_PIN * KEYPAD_columnPins;
	GPIO_PORT* KEYPAD_rowPORTS;
	GPIO_PORT* KEYPAD_columnPORTS;
	uint8_t    KEYPAD_noOfRows;
	uint8_t    KEYPAD_noOfColumns;

}KEYPAD_configStruct;


bool KEYPAD_init(const KEYPAD_configStruct*);

uint8_t KEYPAD_getPressedKey(const KEYPAD_configStruct*);



#endif /* KEYPAD_H_ */
