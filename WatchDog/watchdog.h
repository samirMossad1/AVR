/*
 * 		Module: Watch Dog Reset timer
 *
 *		File Name: gpio.h
 *
 *		Disc: This module gives you full control on WatchDog registers with
 *			  very stable and clear functions
 *
 * 	    Created on: July 16, 2019
 *
 *      Author: Samir Mossad Ibrahim
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_


#include "micro_config.h"
#include "macros.h"
#include "std_types.h"

#define VCC 5


#if (VCC==3)
typedef enum watchdog_prescalar
{

	PRESCALAR_17ms,
	PRESCALAR_34ms,
	PRESCALAR_68ms,
	PRESCALAR_140ms,
	PRESCALAR_270ms,
	PRESCALAR_550ms,
	PRESCALAR_1100ms,
	PRESCALAR_2200ms

}WATCHDOG_PRESCALAR;

#elif (VCC==5)

typedef enum watchdog_prescalar
{

	PRESCALAR_16ms,
	PRESCALAR_32ms,
	PRESCALAR_65ms,
	PRESCALAR_130ms,
	PRESCALAR_260ms,
	PRESCALAR_520ms,
	PRESCALAR_1000ms,
	PRESCALAR_2100ms

}WATCHDOG_PRESCALAR;

#endif








void WATCHDOG_init(const WATCHDOG_PRESCALAR );

void WATCHDOG_enable();

void WATCHDOF_disable();





#endif
