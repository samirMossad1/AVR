
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

	_TRANSMITTER_INTERRUPT,
	_RECEIVER_INTERRUPT,
	_DATA_REG_INTERRUPT


}USART_INTERRUPT_TYPE;


typedef enum
{

	_TRANSMITTER_INTERRUPT_ON,
	_TRANSMITTER_INTERRUPT_OFF

}USART_TRANSMITTER_INTERRUPT;


typedef enum
{
	_RECEIVER_INTERRUPT_ON,
	_RECEIVER_INTERRUPT_OFF

}USART_RECEIVER_INTERRUPT;

typedef enum
{

	_DATA_REGISTER_INTERRUPT_ON,
	_DATA_REGISTER_INTERRUPT_OFF

}USART_DATA_REGISTER_INTERRUPT;

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

	USART_CHARACTER_SIZE 			USART_CS;
	USART_PARITY		 			USART_PARITY;
	USART_STOPBIT					USART_STOP;
	USART_CLOCK_POLARITY			USART_CLOCK;
	USART_TRANSMISSION_SPEED		USART_SPEED;
	USART_TRANSMITTER_INTERRUPT 	USART_TRANS_INT;
	USART_RECEIVER_INTERRUPT		USART_REC_INT;
	USART_DATA_REGISTER_INTERRUPT 	USART_DATA_REG_INT;
	USART_MODE						USART_MODE;
	uint16_t 						USART_baudRate;
	uint16_t                    	Freq_CPU;

}USART_ConfigStruct;







bool USART_init(const USART_ConfigStruct*);

uint8_t USART_receiveByte();

void USART_receiveString(char *);

void USART_sendByte(const uint8_t);

void USART_sendString(const char*);

void USART_setCallBack(const USART_INTERRUPT_TYPE,void(*)(void));

bool USART_disableInterrupt(const USART_INTERRUPT_TYPE);

bool USART_disable();

#endif


