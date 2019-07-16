

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



uint8_t GPIO_readPort(const GPIO_PORT PORT)
{
	switch(PORT)
	{
	case 'PORT_A': return GPIO_PORTA_INPUT_REGISTER;
	case 'PORT_B': return GPIO_PORTB_INPUT_REGISTER;
	case 'PORT_C': return GPIO_PORTC_INPUT_REGISTER;
	case 'PORT_D': return GPIO_PORTD_INPUT_REGISTER;
	default 	 : return GPIO_PORTA_INPUT_REGISTER;
	}
}


uint8_t	GPIO_readPin(const GPIO_PORT PORT, const GPIO_PIN PIN)
{
	switch(PORT)
		{
			case 'PORT_A': return( GPIO_PORTA_INPUT_REGISTER & (1<<PIN) );
			case 'PORT_B': return( GPIO_PORTB_INPUT_REGISTER & (1<<PIN) );
			case 'PORT_C': return( GPIO_PORTC_INPUT_REGISTER & (1<<PIN) );
			case 'PORT_D': return( GPIO_PORTD_INPUT_REGISTER & (1<<PIN) );
			default 	 : return( GPIO_PORTA_INPUT_REGISTER & (1<<PIN) );

		}
}



void	GPIO_writePort(const GPIO_PORT PORT, const uint8_t data)
{
	switch(PORT)
		{
			case 'PORT_A': GPIO_PORTA_OUTPUT_REGISTER=data;
						   	   break;
			case 'PORT_B': GPIO_PORTB_OUTPUT_REGISTER=data;
							   break;
			case 'PORT_C': GPIO_PORTC_OUTPUT_REGISTER=data;
							   break;
			case 'PORT_D': GPIO_PORTD_OUTPUT_REGISTER=data;
							   break;
		}
}


void GPIO_writePin(const GPIO_PORT PORT, const GPIO_PIN PIN,const uint8_t data)
{
	switch(PORT)
		{
			case 'PORT_A':
							RESET_BIT(GPIO_PORTA_OUTPUT_REGISTER,PIN);
							GPIO_PORTA_OUTPUT_REGISTER|=(data & 0x01);
						   	   break;

			case 'PORT_B':
							RESET_BIT(GPIO_PORTB_OUTPUT_REGISTER,PIN);
							GPIO_PORTB_OUTPUT_REGISTER|=(data & 0x01);
						   	   break;


			case 'PORT_C':
							RESET_BIT(GPIO_PORTC_OUTPUT_REGISTER,PIN);
							GPIO_PORTC_OUTPUT_REGISTER|=(data & 0x01);
						   	   break;


			case 'PORT_D':
							RESET_BIT(GPIO_PORTD_OUTPUT_REGISTER,PIN);
							GPIO_PORTD_OUTPUT_REGISTER|=(data & 0x01);
						   	   break;
				}
}

void GPIO_togglePin(const GPIO_PORT PORT , const GPIO_PIN PIN)
{

	switch(PORT)
		{
			case 'PORT_A':
						TOGGLE_BIT(GPIO_PORTA_OUTPUT_REGISTER,PIN);
							break;
			case 'PORT_B':
						TOGGLE_BIT(GPIO_PORTB_OUTPUT_REGISTER,PIN);
							break;
			case 'PORT_C':
						TOGGLE_BIT(GPIO_PORTC_OUTPUT_REGISTER,PIN);
							break;
			case 'PORT_D':
						TOGGLE_BIT(GPIO_PORTD_OUTPUT_REGISTER,PIN);
							break;
		}
}
