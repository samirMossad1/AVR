

#include "timer.h"


static bool timer0_overflowMode_init(void);
static bool timer0_pwmMode_init(const TIMER_PWM_SIGNAL);
static bool timer0_compareOnClearMode_init(TIMER_PINS,TIMER_OUTPUT_TYPES);
static bool timer1_overflowMode_init(void);
static bool timer1_compareOnClearMode_init(void);
static bool timer1_pwmMode_init(void);
static bool timer1_inputCaptureMode_init(void);
static bool timer2_overflowMode_init(void);
static bool timer2_pwmMode_init(const TIMER_PWM_SIGNAL);
static bool timer2_compareOnClearMode_init(TIMER_PINS,TIMER_OUTPUT_TYPES);

static void (*TIMER_callBackPtrs[8])(void)=
{
		NULL_PTR,   /*TIMER0 OVERFLOW*/
		NULL_PTR,   /*TIMER0 COMPARE*/
		NULL_PTR,	/*TIMER1 OVERFLOW*/
		NULL_PTR,	/*TIMER1A COMPARE*/
		NULL_PTR,	/*TIMER1B COMPARE*/
		NULL_PTR,	/*TIMER1 INPUT CAPTURE*/
		NULL_PTR,	/*TIMER2 OVERFLOW*/
		NULL_PTR,	/*TIMER2 COMPARE*/

};



bool TIMER_init(const TIMER_ConfigStruct* timerConfigStruct_ptr)
{

	if(timerConfigStruct_ptr==NULL_PTR)
		return FALSE;


	switch(timerConfigStruct_ptr->TIMER_N)
	{

	case TIMER_0 :

		if(timerConfigStruct_ptr->TIMER_MODE==_CTC_MODE)
		{
			return	timer0_compareOnClearMode_init(timerConfigStruct_ptr->TIMER_PIN,timerConfigStruct_ptr->TIMER_OUT);
		}
		else if(timerConfigStruct_ptr->TIMER_MODE==_PWM_MODE)
		{
			return	timer0_pwmMode_init(timerConfigStruct_ptr->TIMER_PWM);
		}
		else if(timerConfigStruct_ptr->TIMER_MODE==_NORMAL_MODE)
		{
			return	timer0_overflowMode_init();
		}

		break;

	case TIMER_1 :

		if(timerConfigStruct_ptr->TIMER_MODE==_CTC_MODE)
		{
			return	timer2_compareOnClearMode_init(timerConfigStruct_ptr->TIMER_PIN,timerConfigStruct_ptr->TIMER_OUT);
		}
		else if(timerConfigStruct_ptr->TIMER_MODE==_PWM_MODE)
		{
			return	timer2_pwmMode_init(timerConfigStruct_ptr->TIMER_PWM);
		}
		else if(timerConfigStruct_ptr->TIMER_MODE==_NORMAL_MODE)
		{
			return  timer1_overflowMode_init();
		}

		break;


	case TIMER_2 :

		if(timerConfigStruct_ptr->TIMER_MODE==_CTC_MODE)
		{
			return	timer2_compareOnClearMode_init(timerConfigStruct_ptr->TIMER_PIN,timerConfigStruct_ptr->TIMER_OUT);
		}
		else if(timerConfigStruct_ptr->TIMER_MODE==_PWM_MODE)
		{
			return	timer2_pwmMode_init(timerConfigStruct_ptr->TIMER_PWM);
		}
		else if(timerConfigStruct_ptr->TIMER_MODE==_NORMAL_MODE)
		{
			return	timer2_overflowMode_init();
		}

		break;

	default: return FALSE;

	}

}




bool TIMER_enable(const TIMER_NUMBER TIMER_NUM,const TIMER_PRESCALAR TIMER_PRE)
{

	switch(TIMER_NUM)
	{

	case TIMER_0 : CLEAR_N_BITS_THEN_OR(TIMER0_CONTROL_REGISTER,CLOCK_TIMER_DISABLE_MASK,TIMER_PRE,0);
	break;

	case TIMER_1 : CLEAR_N_BITS_THEN_OR(TIMER1B_CONTROL_REGISTER,CLOCK_TIMER_DISABLE_MASK,TIMER_PRE,0);
	break;


	case TIMER_2 : CLEAR_N_BITS_THEN_OR(TIMER2_CONTROL_REGISTER,CLOCK_TIMER_DISABLE_MASK,TIMER_PRE,0);
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
		else if (TIMER_FLAG == _INPUT_CAPTURE)
		{
			return MASK_BITS(TIMER_FLAG_REGISTER,TIMER1_INPUT_CAPTURE_FLAG);
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



bool TIMER_interruptEnable(const TIMER_NUMBER TIMER_NUMBER,const TIMER_CHANNEL TIMER_CHAN,const TIMER_FLAG TIMER_FLAG,void(*CallBack_ptr)(void))
{

	if(CallBack_ptr == NULL_PTR)
		return FALSE;

	switch(TIMER_NUMBER)
	{

	case TIMER_0 : if(TIMER_FLAG == _OVERFLOW)
	{

		TIMER_callBackPtrs[0]=CallBack_ptr;
		SET_BIT(TIMER_FLAG_REGISTER,TIMER0_OVERFLOW_FLAG);
		SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER0_OVERFLOW_INTERRUPT_ENABLE);
	}
	else
	{

		TIMER_callBackPtrs[1]=CallBack_ptr;
		SET_BIT(TIMER_FLAG_REGISTER,TIMER0_COMPARE_FLAG);
		SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER0_COMPARE_INTERRUPT_ENABLE);
	}
	break;


	case TIMER_1 :if(TIMER_FLAG == _OVERFLOW)
	{

		TIMER_callBackPtrs[2]=CallBack_ptr;
		SET_BIT(TIMER_FLAG_REGISTER,TIMER1_OVERFLOW_FLAG);
		SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1_OVERFLOW_INTERRUPT_ENABLE);
	}
	else if(TIMER_FLAG == _INPUT_CAPTURE)
	{

		TIMER_callBackPtrs[5]=CallBack_ptr;
		SET_BIT(TIMER_FLAG_REGISTER,TIMER1_INPUT_CAPTURE_FLAG);
		SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1_INPUT_CAPTURE_INTERRUPT_ENABLE);

	}
	else
	{
		if(TIMER_CHAN == _CHANNEL_A)
		{

			TIMER_callBackPtrs[3]=CallBack_ptr;
			SET_BIT(TIMER_FLAG_REGISTER,TIMER1A_COMPARE_FLAG);
			SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1A_COMPARE_INTERRUPT_ENABLE);
		}
		else
		{
			TIMER_callBackPtrs[4]=CallBack_ptr;
			SET_BIT(TIMER_FLAG_REGISTER,TIMER1B_COMPARE_FLAG);
			SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1B_COMPARE_INTERRUPT_ENABLE);
		}


	}
	break;


	case TIMER_2 : if(TIMER_FLAG == _OVERFLOW)
	{

		TIMER_callBackPtrs[6]=CallBack_ptr;
		SET_BIT(TIMER_FLAG_REGISTER,TIMER2_OVERFLOW_FLAG);
		SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER2_OVERFLOW_INTERRUPT_ENABLE);
	}
	else
	{

		TIMER_callBackPtrs[7]=CallBack_ptr;
		SET_BIT(TIMER_FLAG_REGISTER,TIMER2_COMPARE_FLAG);
		SET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER2_COMPARE_INTERRUPT_ENABLE);
	}
	break;


	}



	return TRUE;
}

bool TIMER_interruptDisable(const TIMER_NUMBER TIMER_NUMBER,const TIMER_CHANNEL TIMER_CHAN,const TIMER_FLAG TIMER_FLAG)
{

	switch(TIMER_NUMBER)
	{

	case TIMER_0 : if(TIMER_FLAG == _OVERFLOW)  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER0_OVERFLOW_INTERRUPT_ENABLE);
	else		    RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER0_COMPARE_INTERRUPT_ENABLE);
	break;


	case TIMER_1 :
		if(TIMER_FLAG == _OVERFLOW)
		{
			RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1_OVERFLOW_INTERRUPT_ENABLE);
		}
		else if(TIMER_FLAG == _INPUT_CAPTURE)
		{

			RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1_INPUT_CAPTURE_INTERRUPT_ENABLE);

		}
		else
		{
			if(TIMER_CHAN == _CHANNEL_A)  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1A_COMPARE_INTERRUPT_ENABLE);
			else			  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER1B_COMPARE_INTERRUPT_ENABLE);


		}
		break;


	case TIMER_2 : if(TIMER_FLAG == _OVERFLOW)  RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER2_OVERFLOW_INTERRUPT_ENABLE);
	else			    RESET_BIT(TIMER_INTERRUPT_MASK_REGISTER,TIMER2_COMPARE_INTERRUPT_ENABLE);
	break;


	}


	return TRUE;
}




void TIMER_COMPARE_setValue(const TIMER_NUMBER TIMER_NUMBER ,const TIMER_CHANNEL TIMER_CHANNEL,const TIMER_MODE TIMER_MODE,const uint16_t compareValue)
{
	uint16_t modifiedValue;

	if(TIMER_NUMBER == TIMER_1)
	{

		if(TIMER_MODE == _PWM_MODE)				modifiedValue= (compareValue*65535)/100;
		else									modifiedValue= compareValue;

		if(TIMER_CHANNEL == _CHANNEL_A)			TIMER1A_COMPARE_REGISTER=modifiedValue;
		else if(TIMER_CHANNEL == _CHANNEL_B)	TIMER1B_COMPARE_REGISTER=modifiedValue;
	}
	else
	{

		if(TIMER_MODE == _CTC_MODE)  		modifiedValue= compareValue & 0x00FF;
		else if(TIMER_MODE == _PWM_MODE)	modifiedValue = (compareValue*255)/100;

		if(TIMER_NUMBER== TIMER_0)			TIMER0_COMPARE_REGISTER= modifiedValue;
		else 								TIMER2_COMPARE_REGISTER= modifiedValue;
	}


}


void TIMER_ICU_setEdge(const TIMER_ICU_EDGE TIMER_EDGE)
{

	CLEAR_N_BITS_THEN_OR(TIMER1B_CONTROL_REGISTER,TIMER_ICU_EGE_CLEAR_MASK,TIMER_EDGE,BIT_6);

}

uint16_t TIMER1_ICU_readCaptureReg()
{
	return TIMER1_INPUT_CAPTURE_REGISTER;
}




static bool timer0_overflowMode_init(void)
{
	TIMER0_CONTROL_REGISTER=TIMER_OVERFLOW_MODE_MASK;
	return TRUE;
}


static bool timer0_compareOnClearMode_init(TIMER_PINS TIMER_PIN,TIMER_OUTPUT_TYPES TIMER_OUTPUT)
{

	TIMER0_CONTROL_REGISTER=0x00;



	if(TIMER_PIN==_NORMAL_PIN)
	{
		TIMER0_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_NORMAL_PIN_MASK;
	}
	else
	{
		SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,BIT_3);

		if(TIMER_OUTPUT==_OUTPUT_COMPARE_TOGGLE)
			TIMER0_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_OC_TOGGLE_PIN_MASK;
		else if(TIMER_OUTPUT==_OUTPUT_COMPARE_CLEAR)
			TIMER0_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_OC_CLEAR_PIN_MASK;
		else if(TIMER_OUTPUT==_OUTPUT_COMPARE_SET)
			TIMER0_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_OC_SET_PIN_MASK;
	}


	return TRUE;

}
static bool timer0_pwmMode_init(const TIMER_PWM_SIGNAL TIMER_PWM)
{

	TIMER0_CONTROL_REGISTER=0x00;

	if(TIMER_PWM==_NON_INVERTING)
		TIMER0_CONTROL_REGISTER|=TIMER_PWM_MODE_NON_INVERTED_MASK;

	else if(TIMER_PWM==_INVERTING)
		TIMER0_CONTROL_REGISTER|=TIMER_PWM_MODE_INVERTED_MASK;

	return TRUE;

}

static bool timer2_overflowMode_init(void)
{
	TIMER2_CONTROL_REGISTER=TIMER_OVERFLOW_MODE_MASK;
	return TRUE;
}


static bool timer2_compareOnClearMode_init(TIMER_PINS TIMER_PIN,TIMER_OUTPUT_TYPES TIMER_OUTPUT)
{

	TIMER0_CONTROL_REGISTER=0x00;



	if(TIMER_PIN==_NORMAL_PIN)
	{
		TIMER2_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_NORMAL_PIN_MASK;
	}
	else
	{
		SET_BIT(GPIO_PORTD_DIRECTION_REGISTER,BIT_7);

		if(TIMER_OUTPUT==_OUTPUT_COMPARE_TOGGLE)
			TIMER2_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_OC_TOGGLE_PIN_MASK;
		else if(TIMER_OUTPUT==_OUTPUT_COMPARE_CLEAR)
			TIMER2_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_OC_CLEAR_PIN_MASK;
		else if(TIMER_OUTPUT==_OUTPUT_COMPARE_SET)
			TIMER2_CONTROL_REGISTER|=TIMER_COMPARE_MODE_WITH_OC_SET_PIN_MASK;
	}


	return TRUE;

}
static bool timer2_pwmMode_init(const TIMER_PWM_SIGNAL TIMER_PWM)
{

	TIMER2_CONTROL_REGISTER=0x00;

	if(TIMER_PWM==_NON_INVERTING)
		TIMER2_CONTROL_REGISTER|=TIMER_PWM_MODE_NON_INVERTED_MASK;

	else if(TIMER_PWM==_INVERTING)
		TIMER2_CONTROL_REGISTER|=TIMER_PWM_MODE_INVERTED_MASK;

	return TRUE;

}

static bool timer1_overflowMode_init(void)
{

	TIMER1A_CONTROL_REGISTER=TIMER1_OVERFLOW_MODE_MASK_A;
	TIMER1B_CONTROL_REGISTER=TIMER1_OVERFLOW_MODE_MASK_B;

	return TRUE;
}

//static bool timer1_compareOnClearMode_init(void)
//static bool timer1_pwmMode_init(void)
//static bool timer1_inputCaptureMode_init(void)




/*ISRs*/

ISR(TIMER0_OVF_vect)
{

	if(TIMER_callBackPtrs[0]!=NULL_PTR)
		(TIMER_callBackPtrs[0])();

}

ISR(TIMER0_COMP_vect)
{

	if(TIMER_callBackPtrs[1]!=NULL_PTR)
		(TIMER_callBackPtrs[1])();

}

ISR(TIMER1_OVF_vect)
{

	if(TIMER_callBackPtrs[2]!=NULL_PTR)
		(TIMER_callBackPtrs[2])();

}

ISR(TIMER1_COMPA_vect)
{


	if(TIMER_callBackPtrs[3]!=NULL_PTR)
		(TIMER_callBackPtrs[3])();

}

ISR(TIMER1_COMPB_vect)
{


	if(TIMER_callBackPtrs[4]!=NULL_PTR)
		(TIMER_callBackPtrs[4])();

}

ISR(TIMER1_CAPT_vect)
{

	if(TIMER_callBackPtrs[5]!=NULL_PTR)
		(TIMER_callBackPtrs[5])();

}


ISR(TIMER2_OVF_vect)
{

	if(TIMER_callBackPtrs[6]!=NULL_PTR)
		(TIMER_callBackPtrs[6])();

}

ISR(TIMER2_COMP_vect)
{

	if(TIMER_callBackPtrs[7]!=NULL_PTR)
		(TIMER_callBackPtrs[7])();

}

