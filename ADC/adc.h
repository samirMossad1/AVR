


#ifndef ADC_H
#define ADC_H



#include "micro_config.h"
#include "std_types.h"
#include "macros.h"



typedef enum adc_refVolt
{
	_AREF,
	_AVCC,
	_INTERNAL=3

}ADC_REFERENCE_VOLATGE;




typedef enum adc_mode
{
	_NO_INTERRUPT,
	_INTERRUPT

}ADC_MODE;

typedef enum adc_prescalar
{
	_FCPU_2,
	_FCPU_4=2,
	_FCPU_8,
	_FCPU_16,
	_FCPU_32,
	_FCPU_64,
	_FCPU_128

}ADC_PRESCALAR;


typedef enum adc_triggersource
{
	_Free_RUNNING,
	_ANALOG_COMPARATOR,
	_EXTERNAL_INT0,
	_TIMER0_COMPARE,
	_TIMER0_OVERFLOW,
	_TIMER1B_COMARE,
	_TIMER1_OVERFLOW,
	_TIMER1_INPUT_CAPTURE,
	_NO_AUTO_TRIGGERING,

}ADC_TRIGGER_SOURCE;


typedef enum adc_speedmode
{
	_OFF,
	_ON

}ADC_HIGH_SPEED;


typedef struct adc_configstruct
{
		ADC_TRIGGER_SOURCE	  ADC_TRIGGER;
		ADC_PRESCALAR		  ADC_SCALAR;
		ADC_REFERENCE_VOLATGE ADC_VOLTAGE;
		ADC_HIGH_SPEED		  ADC_SPEED;
		ADC_MODE			  ADC_MODE;

}ADC_ConfigStruct;


bool ADC_init(const ADC_ConfigStruct*);

uint16_t ADC_convert(const ADC_CHANNEL);   /*Use this conversion function in case of _NO_INTERRUPTS*/

void ADC_convert(const ADC_CHANNEL,void(*)(void));  /*Use this conversion function in case of _INTERRUPTS*/


#endif
