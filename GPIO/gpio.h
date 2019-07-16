
/*
 * 		Module: General Purpose Input/Output.
 *
 *		File Name: gpio.h
 *
 *		Disc: This module gives you full control on GPIO registers with
 *			  very stable and clear functions
 *
 * 	    Created on: July 16, 2019
 *
 *      Author: Samir Mossad Ibrahim
 */


#ifndef GPIO_H
#define GPIO_H



/*Needed Includes*/

#include "macros.h"
#include "micro_config.h"
#include "std_types.h"




/*This enum is used to declare Levels of GPIO*/
typedef enum gpio_level
{
	_LOW,_HIGH

}GPIO_LEVEL;

typedef enum gpio_type
{
	_INPUT,_OUTPUT

}GPIO_TYPE;

typedef enum interrupt_edge
{
	_LOW_LEVEL,
	_LOGICAL_CHANGE,
	_FALLING_EDGE,
	_RISING_EDGE

}GPIO_INTERRUPT_EDGE;


typedef struct GPIO_port
{

	GPIO_PORT PORT;
	GPIO_TYPE PORT_TYPE;

}GPIO_portConfigStruct;


typedef struct GPIO_pin
{
	GPIO_PORT PORT;
	GPIO_PIN  PIN;
	GPIO_TYPE PIN_TYPE;

}GPIO_pinConfigStruct;


typedef struct GPIO_int
{
	GPIO_INTERRUPT_NUMBER INTERRUPT_NUMBER;
	GPIO_INTERRUPT_EDGE   INTERRUPT_EDGE_SELECT;

}GPIO_intConfigStruct;



bool   GPIO_portInit(const GPIO_portConfigStruct*);

uint8_t GPIO_readPort(const GPIO_PORT);

void	GPIO_writePort(const GPIO_PORT, const uint8_t);

void	GPIO_togglePort(const GPIO_PORT);

bool	GPIO_pinInit(const GPIO_pinConfigStruct*);

uint8_t	GPIO_readPin(const GPIO_PORT , const GPIO_PIN);

void GPIO_writePin(const GPIO_PORT , const GPIO_PIN ,const uint8_t);

void GPIO_togglePin(const GPIO_PORT , const GPIO_PIN);

void GPIO_pinPullUpInit(const GPIO_PORT , const GPIO_PIN );

bool GPIO_interruptInit(const GPIO_intConfigStruct*);

bool GPIO_interruptEnable(const GPIO_INTERRUPT_NUMBER);

bool GPIO_interruptDisable(const GPIO_INTERRUPT_NUMBER);







#endif
