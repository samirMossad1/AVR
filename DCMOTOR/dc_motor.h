
#ifndef DC_MOTOR_H
#define DC_MOTOR_H



#include "micro_config.h"
#include "macros.h"
#include "std_types.h"





typedef struct
{

	GPIO_PORT PORT_INPUT_1;
	GPIO_PORT PORT_INPUT_2;
	GPIO_PIN PIN_INPUT_1;
	GPIO_PIN PIN_INPUT_2;

}DCMOTOR_Structure;




void DCMOTOR_init(const DCMOTOR_Structure *);
void DCMOTOR_moveClockWise(const DCMOTOR_Structure *);
void DCMOTOR_moveAntiClockWise(const DCMOTOR_Structure *);
void DCMOTOR_stop(const DCMOTOR_Structure *);
void DCMOTOR_changeSpeed(const DCMOTOR_Structure *,uint16_t);



#endif
