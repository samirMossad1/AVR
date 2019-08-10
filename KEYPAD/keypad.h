

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "micro_config.h"
#include "std_types.h"
#include "macros.h"



typedef enum
{
	_KEYPAD_3X3,
	_KEYPAD_4X4

}KEYPAD_DIMENSIONS;



typedef struct
{

	GPIO_PIN * KEYPAD_rowPins;
	GPIO_PIN * KEYPAD_columnPins;
	KEYPAD_DIMENSIONS KEYPAD_DIM;

}KEYPAD_configStruct;


bool KEYPAD_init(const KEYPAD_configStruct*);

uint8_t KEYPAD_getPressedKey(const KEYPAD_configStruct*);



#endif /* KEYPAD_H_ */
