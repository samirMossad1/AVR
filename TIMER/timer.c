

#include "timer.h"





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
				   else						   return MASK_BITS(TIMER_FLAG_REGISTER,TIMER0_COMPARE_FLAG);

	case TIMER_1 :
					if(TIMER_FLAG == _OVERFLOW)
					{
						return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1_OVERFLOW_FLAG);
					}
					else
					{
						if(TIMER_CHAN == _CHANNEL_A) return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1A_COMPARE_FLAG);
						else						 return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1B_COMPARE_FLAG);
					}


	case TIMER_2 : if(TIMER_FLAG == _OVERFLOW) return MASK_BITS(TIMER_FLAG_REGISTER,TIMER2_OVERFLOW_FLAG);
				   else						   return MASK_BITS(TIMER_FLAG_REGISTER,TIMER2_COMPARE_FLAG);


	default : return (uint8_t) 0x00;


	}



}

