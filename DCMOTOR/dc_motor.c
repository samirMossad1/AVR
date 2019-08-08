


#include "dc_motor.h"
#include "gpio.h"


bool DCMOTOR_init(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return FALSE;

	GPIO_pinConfigStruct input_1={DCMOTOR_structPtr->PORT_INPUT_1
			,DCMOTOR_structPtr->PIN_INPUT_1
			,_OUTPUT};

	GPIO_pinConfigStruct input_2={DCMOTOR_structPtr->PORT_INPUT_2
			,DCMOTOR_structPtr->PIN_INPUT_2
			,_OUTPUT};


	GPIO_pinInit(&input_1);
	GPIO_pinInit(&input_2) ;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,LOW);


	return TRUE;
}


void DCMOTOR_moveClockWise(const DCMOTOR_Structure * DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,HIGH);

}
void DCMOTOR_moveAntiClockWise(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,HIGH);


}
void DCMOTOR_stop(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,LOW);



}
