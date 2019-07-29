

#include "i2c.h"


#define BIT_RATE(CPU_FR,SCL_FR) (((CPU_FR)/(2*SCL_FR))-8)


static void (*TWI_CallBackPtr_g[2])=
{
		NULL_PTR		/*Transmit CallBack Pointer*/
		,NULL_PTR		/*Receive CallBack Pointer*/
};





ISR(TWI_vect)
{

	/*Transmit*/

	if(TWI_CallBackPtr_g[0] != NULL_PTR)
	{


	}



	/*Receive*/
	if(TWI_CallBackPtr_g[1] != NULL_PTR)
	{


	}




}



bool TWI_init(const TWI_ConfigStruct* TWI_structPtr)
{
	if(TWI_structPtr == NULL_PTR)	return FALSE;

	/*clear register*/
	TWI_CONTROL_REGISTER=0x00;

	/*clear flag*/
	SET_BIT(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG);

	TWI_STATUS_REGISTER&=~(1<<TWI_PRESCALAR_0)&~(1<<TWI_PRESCALAR_1);

	TWI_BIT_RATE_REGISTER=BIT_RATE(TWI_structPtr->CPU_Frequency,TWI_structPtr->SCL_Frequency);

	TWI_ADDRESSE_REGISTER = ( (TWI_structPtr->TWI_addresse)<<BIT_1);


	SET_BIT(TWI_CONTROL_REGISTER,TWI_ENABLE);

	return TRUE;
}

void TWI_start()
{

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_START)|
			(1<<TWI_ENABLE);

	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));
}


void TWI_stop()
{

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_STOP)|
			(1<<TWI_ENABLE);

	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));

}


void TWI_send(uint8_t data)
{
	TWI_DATA_REGISTER=data;

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_ENABLE);

	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));

}


uint8_t TWI_read(const 	TWI_ACKNOWLEDGMENT TWI_ACK)
{

	RESET_BIT(TWI_CONTROL_REGISTER,TWI_ACKNOWLEDGE_ENABLE);

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_ENABLE)|
			(TWI_ACK<<TWI_ACKNOWLEDGE_ENABLE);


	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));

	return TWI_DATA_REGISTER;
}

uint8_t TWI_getStatus()
{

	return (TWI_STATUS_REGISTER & TWI_MASK_STATUS_BITS);

}


uint8_t TWI_getFlag(TWI_FLAG TWI_FLAG)
{

	if(TWI_FLAG==_INTERRUPT_FLAG_TWI)
	{

		return MASK_BITS_THEN_SHIFT_LEFT(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG,BIT_7);

	}
	else
	{

		return MASK_BITS_THEN_SHIFT_LEFT(TWI_CONTROL_REGISTER,TWI_WRITE_COLLISION_FLAG,BIT_3);

	}

}




bool TWI_interruptDisable()
{


	RESET_BIT(TWI_CONTROL_REGISTER,TWI_INTERRUPT_ENABLE);


	return TRUE;
}



bool TWI_disable()
{

	RESET_BIT(TWI_CONTROL_REGISTER,TWI_ENABLE);

	return TRUE;
}




/*
 * INTERRUPTS !!!!
 * */
