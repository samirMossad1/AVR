

#include "i2c.h"



/*Macros*/

#define BIT_RATE(CPU_FR,SCL_FR) (((CPU_FR)/(2*SCL_FR))-8)
#define SENT 		(1U)
#define RECEIVED	(0U)


/*Prototypes*/
static uint8_t TWI_ReceiveOrSend(uint8_t);



/*Call Back Pointers*/
static void (*TWI_CallBackPtr_g[2])=
{
		NULL_PTR		/*Transmit CallBack Pointer*/
		,NULL_PTR		/*Receive CallBack Pointer*/
};


/*Static Global Variables*/
static volatile uint8_t TWI_currentStatus_g=0x00;
static TWI_INTERRUPT TWI_interruptStatus;


/*Global Variables To Be Externed (For Errors)*/



/*Interrupt Service Routine*/
ISR(TWI_vect)
{


	TWI_currentStatus_g=TWI_ReceiveOrSend(TWI_getStatus());

	if(TWI_currentStatus_g==SENT)
	{

		/*Transmit*/
		if(TWI_CallBackPtr_g[0] != NULL_PTR)
		{
			TWI_CallBackPtr_g[0]();
		}

	}

	else
	{

		/*Receive*/
		if(TWI_CallBackPtr_g[1] != NULL_PTR)
		{
			TWI_CallBackPtr_g[1]();
		}

	}


	/*Clear the interrupt flag*/
	SET_BIT(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG);

}



bool TWI_init(const TWI_ConfigStruct* TWI_structPtr)
{
	if(TWI_structPtr == NULL_PTR)	return FALSE;

	/*clear register*/
	TWI_CONTROL_REGISTER=0x00;

	/*clear flag*/
	SET_BIT(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG);

	TWI_CONTROL_REGISTER|=(TWI_structPtr->TWI_INT<<TWI_INTERRUPT_ENABLE);

	TWI_interruptStatus=(TWI_structPtr->TWI_INT);

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

	if(TWI_interruptStatus != _ENABLE_INTERRUPT)
	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));
}


void TWI_stop()
{

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_STOP)|
			(1<<TWI_ENABLE);


	if(TWI_interruptStatus != _ENABLE_INTERRUPT)
	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));

}


void TWI_send(uint8_t data)
{
	TWI_DATA_REGISTER=data;

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_ENABLE);


	if(TWI_interruptStatus != _ENABLE_INTERRUPT)
	while(BIT_IS_CLEAR(TWI_CONTROL_REGISTER,TWI_INTERRUPT_FLAG));

}


uint8_t TWI_read(const 	TWI_ACKNOWLEDGMENT TWI_ACK)
{

	RESET_BIT(TWI_CONTROL_REGISTER,TWI_ACKNOWLEDGE_ENABLE);

	TWI_CONTROL_REGISTER|=(1<<TWI_INTERRUPT_FLAG)|
			(1<<TWI_ENABLE)|
			(TWI_ACK<<TWI_ACKNOWLEDGE_ENABLE);



	if(TWI_interruptStatus != _ENABLE_INTERRUPT)
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



bool TWI_setInterruptCallBacks(void(*Trans_CallBackPtr)(void),void(*Receive_CallBackPtr)(void))
{

	TWI_CallBackPtr_g[0]=Trans_CallBackPtr;
	TWI_CallBackPtr_g[1]=Receive_CallBackPtr;

	return TRUE;
}

bool TWI_interruptDisable()
{


	RESET_BIT(TWI_CONTROL_REGISTER,TWI_INTERRUPT_ENABLE);

	TWI_CallBackPtr_g[0]=NULL_PTR;
	TWI_CallBackPtr_g[1]=NULL_PTR;


	return TRUE;
}


bool TWI_disable()
{

	RESET_BIT(TWI_CONTROL_REGISTER,TWI_ENABLE);

	return TRUE;
}



static uint8_t TWI_ReceiveOrSend(uint8_t status)
{

	switch(status)
	{

	case  TWI_MASTER_START_CONDITION_SENT:
	case  TWI_MASTER_REPEATED_START_CONDITION_SENT:
	case  TWI_MASTER_SLAVE_ADD_WITH_WRITE_SENT_ACK_RECEIVED:
	case  TWI_MASTER_SLAVE_ADD_WITH_WRITE_SENT_NO_ACK_RECEIVED:
	case  TWI_MASTER_SLAVE_ADD_WITH_READ_SENT_ACK_RECEIVED:
	case  TWI_MASTER_SLAVE_ADD_WITH_READ_SENT_NO_ACK_RECEIVED:
	case  TWI_MASTER_DATA_BYTE_TRANSMITTED_WITH_ACK_RECEIVED:
	case  TWI_MASTER_DATA_BYTE_TRANSMITTED_WITH_NO_ACK_RECEIVED:
	case  TWI_SLAVE_DATA_BYTE_TRANSMITTED_WITH_ACK_RECEIVED:
	case  TWI_SLAVE_DATA_BYTE_TRANSMITTED_WITH_NO_ACK_RECEIVED:	return SENT;

	case TWI_MASTER_DATA_BYTE_RECEIVED_WITH_ACK_TRANSMITTED:
	case TWI_MASTER_DATA_BYTE_RECEIVED_WITH_ACK_TRANSMITTED:
	case TWI_SLAVE_REPEATED_START_CONDITION_RECEIVED:
	case TWI_SLAVE_SLAVE_ADD_WITH_WRITE_RECEIVED_ACK_SENT:
	case TWI_SLAVE_SLAVE_ADD_WITH_READ_RECEIVED_ACK_SENT:
	case TWI_SLAVE_DATA_BYTE_RECEIVED_WITH_ACK_TRANSMITTED:
	case TWI_SLAVE_DATA_BYTE_RECEIVED_WITH_NO_ACK_TRANSMITTED: return RECEIVED;


	default: return SENT;
	}


}

