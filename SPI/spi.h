
#ifndef SPI_H_
#define SPI_H_




#include "micro_config.h"
#include "std_types.h"
#include "macros.h"







typedef enum spi_device
{

	_SLAVE,
	_MASTER

}SPI_DEVICE;


typedef enum spi_mode
{
	_SPI_NO_INTERRUPT,
	_SPI_INTERRUPT

}SPI_INTERRUPT;


typedef enum spi_prescalar
{
	F_CPU_4,
	F_CPU_16,
	F_CPU_64,
	F_CPU_128

}SPI_FREQUENCY_PRESCALAR;


typedef enum spi_speed
{

	_SPI_NORMAL_SPEED,
	_SPI_DOUBLE_SPEED

}SPI_TRANSMISSION_SPEED;


typedef enum spi_dataorder
{
	_LSB_FIRST,
	_MSB_FIRST

}SPI_DATA_ORDER;


typedef enum spi_polarity
{

	_LEADING_FALLING_EDGE,
	_LEADING_RISING_EDGE

}SPI_POLARITY;

typedef enum spi_phase
{

	_SAMPLE_ON_LEADING_SETUP_ON_TRAILING,
	_SAMPLE_ON_TRAILING_SETUP_ON_LEADING,

}SPI_CLOCK_PHASE;




typedef struct spi_configstruct
{


	SPI_FREQUENCY_PRESCALAR  	SPI_FREQ_PRE;
	SPI_CLOCK_PHASE				SPI_CLCK_PHASE;
	SPI_POLARITY				SPI_CLCK_POLARITY;
	SPI_DEVICE					SPI_DEVICE_TYPE;
	SPI_TRANSMISSION_SPEED		SPI_SPEED;
	SPI_INTERRUPT				SPI_INT;
	SPI_DATA_ORDER				SPI_DATA_ORDER;

}SPI_ConfigStruct;




bool SPI_deviceInit(const SPI_ConfigStruct *);

uint8_t SPI_readByte();

void SPI_readString(char *);

void SPI_sendByte(uint8_t);

void SPI_sendString(const char *);

uint8_t SPI_readStatus();

bool SPI_disable();

void SPI_setCallBack(void(*)(void));

bool SPI_disableInterrupt();

#endif
