
/*
 * 		Module: Microcontroller Configurations.
 *
 *		File Name: micro_config.h
 *
 * 	    Created on: July 16, 2019
 *
 *      Author: Samir Mossad Ibrahim
 */


#ifndef MICRO_CONFIG_H
#define MICRO_CONFIG_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



typedef enum port
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D

}GPIO_PORT;

typedef enum pin
{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6

}GPIO_PIN;

typedef enum extinterrupt
{
	INTERRUPT_0,
	INTERRUPT_1,
	INTERRUPT_2

}GPIO_INTERRUPT_NUMBER;



















#endif
