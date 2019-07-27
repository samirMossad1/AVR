
#ifndef I2C_H_
#define I2C_H_




#include "micro_config.h"
#include "std_types.h"
#include "macros.h"




typedef enum
{
	_DISABLE_INTERRUPT,
	_ENABLE_INTERRUPT

}TWI_INTERRUPT;

typedef enum
{
	_ACK_DISABLE,
	_ACK_ENABLE

}TWI_ACKNOWLEDGMENT;


typedef struct twi_configstruct
{

	TWI_INTERRUPT	   TWI_INT;
	TWI_ACKNOWLEDGMENT TWI_ACK;
	uint8_t 		   TWI_addresse;
	uint32_t 		   CPU_Frequency;
	uint32_t		   SCL_Frequency;

}TWI_ConfigStruct;



bool TWI_init(const TWI_ConfigStruct*);

void TWI_start();

void TWI_stop();

void TWI_send(uint8_t);

void TWI_read(const TWI_ACKNOWLEDGMENT);

uint8_t TWI_getFlag(uint8_t);

uint8_t TWI_getStatus();

bool TWI_interruptDisable();

bool TWI_disable();





#endif
