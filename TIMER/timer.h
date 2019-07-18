
#ifndef TIMER_H_
#define TIMER_H_


#include "micro_config.h"
#include "std_types.h"
#include "macros.h"



typedef enum
{
	_NORMAL_MODE, /*Overflow Mode*/
	_CTC_MODE,
	_PWM_MODE

}TIMER_MODE;

typedef enum
{
	_OVERFLOW,
	_COMPARE


}TIMER_FLAG;

typedef enum
{
	_FCPU	=1, /*start from 001*/
	_FCPU_8,
	_FCPU_64,
	_FCPU_256,
	_FCPU_1024

}TIMER_PRESCALAR;

typedef enum
{
	_NORMAL_PIN, /*Choose this option in the normal mode*/
	_OUTPUT_COMPARE_PIN

}TIMER_PINS;

typedef enum
{
	_OUTPUT_COMPARE_DISCONNECTED,
	_OUTPUT_COMPARE_TOGGLE, /*Only in CTC mode*/
	_OUTPUT_COMPARE_CLEAR,
	_OUTPUT_COMPARE_SET,
	__IGNORE


}TIMER_OUTPUT_TYPES;

typedef enum
{
	_NO_INTERRUPT,
	_INTERRUPT

}TIMER_INTERRUPT;

typedef struct timer_configStruct
{

	TIMER_NUMBER 		TIMER_N;
	TIMER_CHANNEL 		TIMER_CH;	 /*use the ignore option in case of timer0/2*/
	TIMER_MODE  		TIMER_MODE;
	TIMER_OUTPUT_TYPES	TIMER_OUT; 	 /*use the ignore option in case of normal mode*/
	TIMER_INTERRUPT 	TIMER_INT;
	void (* CallBack_ptr)(void);	/*in case of No interrupts, set this pointer to NULL_PTR*/
}TIMER_ConfigStruct;





bool TIMER_init(const TIMER_ConfigStruct *);

bool TIMER_enable(const TIMER_NUMBER,const TIMER_CHANNEL,const TIMER_PIN,const TIMER_PRESCALAR);

bool TIMER_disable(const TIMER_NUMBER,const TIMER_CHANNEL);

uint16_t TIMER_readCount(const TIMER_NUMBER);

uint8_t	 TIMER_readStatus(const TIMER_NUMBER,const TIMER_CHANNEL,const TIMER_FLAG);

bool TIMER_interruptDisable(const TIMER_NUMBER,const TIMER_CHANNEL,const TIMER_FLAG);




#endif
