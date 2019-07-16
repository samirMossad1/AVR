

#include "gpio.h"


bool   GPIO_portInit(const GPIO_portConfigStruct* ConfigStructptr)
{

		if(ConfigStructptr == NULL_PTR) return FALSE;

		switch(ConfigStructptr->PORT)
		{

		case 'PORT_A':
			GPIO_PORTA_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
			break;

		case 'PORT_B':
			GPIO_PORTB_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
			break;

		case 'PORT_C':
			GPIO_PORTC_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
			break;

		case 'PORT_D':
			GPIO_PORTD_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
			break;
		}

		return TRUE;
}


bool	GPIO_pinInit(const GPIO_pinConfigStruct* ConfigStructptr)
{

	if(ConfigStructptr == NULL_PTR) return FALSE;

	switch(ConfigStructptr->PORT)
	{

	case 'PORT_A':
				if(ConfigStructptr->PIN_TYPE == _INPUT)
				{
					RESET_BIT(GPIO_PORTA_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				else
				{
					SET_BIT(GPIO_PORTA_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				break;

	case 'PORT_B':
				if(ConfigStructptr->PIN_TYPE == _INPUT)
				{
					RESET_BIT(GPIO_PORTB_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				else
				{
					SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				break;


	case 'PORT_C':
				if(ConfigStructptr->PIN_TYPE == _INPUT)
				{
					RESET_BIT(GPIO_PORTC_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				else
				{
					SET_BIT(GPIO_PORTC_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				break;


	case 'PORT_D':
				if(ConfigStructptr->PIN_TYPE == _INPUT)
				{
					RESET_BIT(GPIO_PORTD_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				else
				{
					SET_BIT(GPIO_PORTD_DIRECTION_REGISTER,ConfigStructptr->PIN);
				}
				break;


	}

	return TRUE;
}
