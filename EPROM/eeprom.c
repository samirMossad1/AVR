
#include "eeprom.h"


#define SLAVE_ADDRESSE_ADJUST_WITH_WRITE_COMMAND(X) ( (((0xA0) | (X>>7)) & ~(0X01)) )
#define SLAVE_ADDRESSE_ADJUST_WITH_READ_COMMAND(X)  ( (((0xA0) | (X>>7)) |  (0X01)) )






void EEPROM_init(const TWI_ConfigStruct* twiConfigStruct_ptr)
{

	TWI_init(twiConfigStruct_ptr);

}


uint8_t EEPROM_writeByte(const uint16_t addresse_t,const uint8_t data_t)
{


	TWI_start();
	if(TWI_getStatus()!=TWI_MASTER_START_CONDITION_SENT)
		return FALSE;


	TWI_send( SLAVE_ADDRESSE_ADJUST_WITH_WRITE_COMMAND(addresse_t) );
	if(TWI_getStatus()!=TWI_MASTER_SLAVE_ADD_WITH_WRITE_SENT_ACK_RECEIVED)
		return FALSE;

	TWI_send((uint8_t)(addresse_t));
	if(TWI_getStatus()!=TWI_MASTER_DATA_BYTE_TRANSMITTED_WITH_ACK_RECEIVED)
		return FALSE;

	TWI_send(data_t);
	if(TWI_getStatus()!=TWI_MASTER_DATA_BYTE_TRANSMITTED_WITH_ACK_RECEIVED)
		return FALSE;


	TWI_stop();


	return TRUE;
}


