
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

#include "../macros.h"
#include "../micro_config.h"
#include "../std_types.h"




/*This enum is used to declare Levels of GPIO*/
typedef enum level
{
	_LOW,_HIGH

}GPIO_LEVEL;


typedef struct GPIO_port
{

}GPIO_portConfigStruct;


typedef struct GPIO_pin
{

}GPIO_pinConfigStruct;


typedef struct GPIO_int
{

}GPIO_intConfigStruct;



bool   GPIO_portInit(const GPIO_portConfigStruct*);

uint8_t GPIO_readPort(const GPIO_PORT);

void	GPIO_writePort(const GPIO_PORT, const uint8_t);

void	GPIO_togglePort(const GPIO_PORT);



bool	GPIO_pinInit(const GPIO_pinConfigStruct*);

uint8_t	GPIO_readPin(const GPIO_PORT , const GPIO_PIN);

void GPIO_writePin(const GPIO_PORT , const GPIO_PIN ,const uint8_t);

void GPIO_togglePin(const GPIO_PORT , const GPIO_PIN);





bool GPIO_intEnable(const GPIO_INTERRUPT_NUMBER);

bool GPIO_intDisable(const GPIO_INTERRUPT_NUMBER);

bool GPIO_intInitialize(const GPIO_intConfigStruct*);












#endif
