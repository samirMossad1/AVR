

#ifndef EEPROM_H_
#define EEPROM_H_

#include "micro_config.h"
#include "std_types.h"
#include "macros.h"

#include "i2c.h"




void EEPROM_init(const TWI_ConfigStruct*);
uint8_t EEPROM_writeByte(const uint16_t,const uint8_t);
uint8_t	EEPROM_readByte(const uint16_t,uint8_t*);


#endif
