
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


/*This enum is used to declare the type of GPIO*/
typedef enum gpio_type
{
	_INPUT,_OUTPUT

}GPIO_TYPE;


/*This enum is used to declare selected edge of the external interrupt of GPIO*/
typedef enum interrupt_edge
{
	_LOW_LEVEL,
	_LOGICAL_CHANGE,
	_FALLING_EDGE,
	_RISING_EDGE

}GPIO_INTERRUPT_EDGE;


/*This is structure is used to initialize any GPIO_PORT*/
typedef struct GPIO_port
{

	GPIO_PORT PORT;
	GPIO_TYPE PORT_TYPE;

}GPIO_portConfigStruct;



/*This is structure is used to initialize any GPIO_PIN*/
typedef struct GPIO_pin
{
	GPIO_PORT PORT;
	GPIO_PIN  PIN;
	GPIO_TYPE PIN_TYPE;

}GPIO_pinConfigStruct;


/*This is structure is used to initialize any GPIO External Interrupt*/
typedef struct GPIO_int
{
	GPIO_INTERRUPT_NUMBER INTERRUPT_NUMBER;
	GPIO_INTERRUPT_EDGE   INTERRUPT_EDGE_SELECT;

}GPIO_intConfigStruct;





/* ------------------------------------------------------------
 *Function-Name:GPIO_portInit
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool   GPIO_portInit(const GPIO_portConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name: GPIO_readPort
 *
 *Description:
 *
 *Inputs:
 *
 *Returns: the value of the data register
 *
 *--------------------------------------------------------------*/
uint8_t GPIO_readPort(const GPIO_PORT);


/* ------------------------------------------------------------
 *Function-Name:GPIO_writePort
 *
 *Description:
 *
 *Inputs:
 *
 *Returns: void
 *
 *--------------------------------------------------------------*/
void	GPIO_writePort(const GPIO_PORT, const uint8_t);


/* ------------------------------------------------------------
 *Function-Name:GPIO_togglePort
 *
 *Description:
 *
 *Inputs:
 *
 *Returns: void
 *
 *--------------------------------------------------------------*/
void	GPIO_togglePort(const GPIO_PORT);



/* ------------------------------------------------------------
 *Function-Name:GPIO_togglePort
 *
 *Description:
 *
 *Inputs:
 *
 *Returns: void
 *
 *--------------------------------------------------------------*/
void GPIO_portPullUpInit(const GPIO_PORT);

/* ------------------------------------------------------------
 *Function-Name:GPIO_pinInit
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool	GPIO_pinInit(const GPIO_pinConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_readPin
 *
 *Description:
 *
 *Inputs:
 *
 *Returns: the value of the corresponding pin in the data register
 *
 *--------------------------------------------------------------*/
uint8_t	GPIO_readPin(const GPIO_PORT , const GPIO_PIN);


/* ------------------------------------------------------------
 *Function-Name:GPIO_writePin
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:	void
 *
 *--------------------------------------------------------------*/
void GPIO_writePin(const GPIO_PORT , const GPIO_PIN ,const uint8_t);


/* ------------------------------------------------------------
 *Function-Name:GPIO_togglePin
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:	void
 *
 *--------------------------------------------------------------*/
void GPIO_togglePin(const GPIO_PORT , const GPIO_PIN);


/* ------------------------------------------------------------
 *Function-Name:GPIO_pinPullupInit
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:	void
 *
 *--------------------------------------------------------------*/
void GPIO_pinPullUpInit(const GPIO_PORT , const GPIO_PIN );


/* ------------------------------------------------------------
 *Function-Name:GPIO_interruptInit
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool GPIO_interruptInit(const GPIO_intConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_interruptEnable
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool GPIO_interruptEnable(const GPIO_INTERRUPT_NUMBER);


/* ------------------------------------------------------------
 *Function-Name:GPIO_interruptDisable
 *
 *Description:
 *
 *Inputs:
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool GPIO_interruptDisable(const GPIO_INTERRUPT_NUMBER);







#endif
