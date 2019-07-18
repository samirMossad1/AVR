

#include "timer.h"





bool TIMER_enable(const TIMER_NUMBER TIMER_NUM,const TIMER_CHANNEL TIMER_CHAN,const TIMER_PRESCALAR TIMER_PRE)
{

	switch(TIMER_NUM)
	{

	case TIMER_0 : CLEAR_N_BITS_THEN_OR(TIMER0_CONTROL_REGISTER,CLOCK_TIMER_DISABLE_MASK,TIMER_PRE);
					break;

	case TIMER_1 : CLEAR_N_BITS_THEN_OR(TIMER1B_CONTROL_REGISTER,CLOCK_TIMER_DISABLE_MASK,TIMER_PRE);
					break;


	case TIMER_2 : CLEAR_N_BITS_THEN_OR(TIMER2_CONTROL_REGISTER,CLOCK_TIMER_DISABLE_MASK,TIMER_PRE);
					break;

	}



	return TRUE;
}




bool TIMER_disable(const TIMER_NUMBER TIMER_NUM)
{


	switch(TIMER_NUM)
	{

	case TIMER_0 : TIMER0_CONTROL_REGISTER &= ~(CLOCK_TIMER_DISABLE_MASK);
	break;


	case TIMER_1 : TIMER1B_CONTROL_REGISTER &= ~(CLOCK_TIMER_DISABLE_MASK);
	break;

	case TIMER_2 : TIMER2_CONTROL_REGISTER &= ~(CLOCK_TIMER_DISABLE_MASK);
	break;

	}




	return TRUE;
}



uint16_t TIMER_readCount(const TIMER_NUMBER TIMER_NUM)
{

	switch(TIMER_NUM)
	{

	case TIMER_0 : 	return (uint16_t) TIMER0_COUNT_REGISTER;

	case TIMER_1 :  return 			  TIMER1_COUNT_REGISTER;

	case TIMER_2 :	return (uint16_t) TIMER2_COUNT_REGISTER;

	default :		return (uint16_t) TIMER0_COUNT_REGISTER;


	}

}

uint8_t	 TIMER_readStatus(const TIMER_NUMBER TIMER_NUM,const TIMER_CHANNEL TIMER_CHAN,const TIMER_FLAG TIMER_FLAG)
{

	switch(TIMER_NUM)
	{

	case TIMER_0 : if(TIMER_FLAG == _OVERFLOW) return MASK_BITS(TIMER_FLAG_REGISTER,TIMER0_OVERFLOW_FLAG);
	else		   return MASK_BITS(TIMER_FLAG_REGISTER,TIMER0_COMPARE_FLAG);

	case TIMER_1 :
		if(TIMER_FLAG == _OVERFLOW)
		{
			return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1_OVERFLOW_FLAG);
		}
		else
		{
			if(TIMER_CHAN == _CHANNEL_A) return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1A_COMPARE_FLAG);
			else			     return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1B_COMPARE_FLAG);
		}


	case TIMER_2 : if(TIMER_FLAG == _OVERFLOW) return MASK_BITS(TIMER_FLAG_REGISTER,TIMER2_OVERFLOW_FLAG);
	else		   return MASK_BITS(TIMER_FLAG_REGISTER,TIMER2_COMPARE_FLAG);


	default : return (uint8_t) 0x00;


	}

}




bool TIMER_interruptDisable(const TIMER_NUMBER TIMER_NUMBER,const TIMER_CHANNEL TIMER_CHAN,const TIMER_FLAG TIMER_FLAG)
{

	switch(TIMER_NUMBER)
	{

	case TIMER_0 : if(TIMER_FLAG == _OVERFLOW)  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER0_OVERFLOW_FLAG);
	else		    RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER0_COMPARE_FLAG);
	break;


	case TIMER_1 :
		if(TIMER_FLAG == _OVERFLOW)
		{
			RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1_OVERFLOW_FLAG);
		}
		else
		{
			if(TIMER_CHAN == _CHANNEL_A)  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1A_COMPARE_FLAG);
			else			      RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1B_COMPARE_FLAG);
		}
		break;


	case TIMER_2 : if(TIMER_FLAG == _OVERFLOW)  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER2_OVERFLOW_FLAG);
	else			    RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER2_COMPARE_FLAG);
	break;


	}


	return TRUE;
}

