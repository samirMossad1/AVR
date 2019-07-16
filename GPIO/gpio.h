
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






#endif
