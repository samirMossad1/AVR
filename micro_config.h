
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






/**  GPIO REGISTERS  **/


#define GPIO_PORTA_DIRECTION_REGISTER		DDRA
#define GPIO_PORTA_OUTPUT_REGISTER			PORTA
#define GPIO_PORTA_INPUT_REGISTER			PINA

#define GPIO_PORTB_DIRECTION_REGISTER		DDRB
#define GPIO_PORTB_OUTPUT_REGISTER			PORTB
#define GPIO_PORTB_INPUT_REGISTER			PINB

#define GPIO_PORTC_DIRECTION_REGISTER		DDRC
#define GPIO_PORTC_OUTPUT_REGISTER			PORTC
#define GPIO_PORTC_INPUT_REGISTER			PINC

#define GPIO_PORTD_DIRECTION_REGISTER		DDRD
#define GPIO_PORTD_OUTPUT_REGISTER			PORTD
#define GPIO_PORTD_INPUT_REGISTER			PIND








#endif
