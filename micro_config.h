
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


/** Magical Numbers **/

#define GPIO_INT01_OFFSET			(0X06)
#define GPIO_INT1_OFFSET			(0X07)
#define GPIO_INT2_OFFSET			(0X05)
#define BIT_0						(0X0)
#define BIT_1						(0X1)
#define BIT_2						(0X2)
#define BIT_3						(0X3)
#define BIT_4						(0X4)
#define BIT_5						(0X5)
#define BIT_6						(0X6)
#define BIT_7						(0X7)




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


#define GPIO_MODULE_INTERRUPT_CONTROL_REGISTER 	GICR
#define GPIO_INTERRUPT_SENSE_CONTROL_REGISTER 	MCUCR
#define GPIO_MASKED_INTERRUPT_FLAG_REGISTER 	GIFR



/** WATCHDOG RESET TIMER REGISTERS **/

#define MCU_CONTROL_STATUS_REGISTER				MCUCSR
#define WATCHDOG_TIMER_CONTROL_REGISTER			WDTCR





/** Enums which are related to the micro controller arch. **/

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
