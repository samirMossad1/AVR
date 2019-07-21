
#ifndef USART_H_
#define USART_H_



#include "micro_config.h"
#include "macros.h"
#include "std_types.h"





typedef enum
{
	_NORMAL_SPEED,
	_DOUBLE_SPEED

}USART_TRANSMISSION_SPEED;


typedef enum
{

	_NO_INTERRUPT,
	_INTERRUPT

}USART_INTERRUPT_ENABLE;


typedef enum
{

	_ASYNCHRONOUS,
	_SYNCHRONOUS

}USART_MODE;


typedef enum
{
	_DISABLED,
	_EVEN_PARITY=2,
	_ODD_PARITY

}USART_PARITY;

typedef enum
{
	_1_BIT,
	_2_BITS

}USART_STOPBIT;

typedef enum
{

	_5_BIT,
	_6_BIT,
	_7_BIT,
	_8_BIT,
	_9_BIT=7

}USART_CHARACTER_SIZE;

typedef enum
{
	_TRANS_RISING_RECIEVE_FALLING,
	_TRANS_FALLING_RECIEVE_RISING,
	_IGNORE

}USART_CLOCK_POLARITY;



typedef struct usart_configstruct
{

	USART_CHARACTER_SIZE 		USART_CS;
	USART_PARITY		 		USART_PARITY;
	USART_STOPBIT				USART_STOP;
	USART_CLOCK_POLARITY		USART_CLOCK;
	USART_TRANSMISSION_SPEED	USART_SPEED;
	USART_INTERRUPT_ENABLE		USART_INT;
	USART_MODE					USART_MODE;
	uint16_t 					USART_baudRate;


}USART_ConfigStruct;







bool USART_init(const USART_ConfigStruct);

uint8_t USART_receiveByte();

void USART_receiveString(char *);

void USART_sendByte(const uint8_t);

void USART_sendString(const char*);

bool USART_disable();

#endif


