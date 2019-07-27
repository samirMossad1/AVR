
#ifndef I2C_H_
#define I2C_H_




#include "micro_config.h"
#include "std_types.h"
#include "macros.h"



typedef enum
{
	_INTERRUPT_FLAG_TWI,
	_WRITE_COLLISION_FLAG_TWI

}TWI_FLAG;


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
	void(*TWI_callBackPtr)(void);   /*In case of _DISABLE_INTERRUPT , set this pointer to Null (it is ignored)*/

}TWI_ConfigStruct;



bool TWI_init(const TWI_ConfigStruct*);

void TWI_start();

void TWI_stop();

void TWI_send(uint8_t);

uint8_t TWI_read();

uint8_t TWI_getFlag(const TWI_FLAG);

uint8_t TWI_getStatus();

bool TWI_interruptDisable();

bool TWI_disable();





#endif
