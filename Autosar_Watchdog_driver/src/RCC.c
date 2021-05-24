/*
 * RCC.c
 *
 *  Created on: Jan 29, 2021
 *      Author: andrew
 */


#include "../../lib/src/Std_Types.h"
#include "../../lib/src/Bit_Mask.h"
#include "RCC.h"
#include "RCC_cfg.h"
#include "../../lib/src/errorCode.h"





#define RCC_BASE_ADDRESS  		0x40023800


/**
 * RCC preferal Registers are assigned in structure to access them sequinally
 */
typedef   struct{
	uint32_t	CR    		    ;
	uint32_t	PLLCFGR 		;
	uint32_t	CFGR   			;
	uint32_t	CIR    			;
	uint32_t	AHB1RSTR		;
	uint32_t	AHB2RSTR	    ;
	uint32_t	AHB3RSTR		;
	uint32_t	Reserved1		;
	uint32_t	APB1RSTR		;
	uint32_t	APB2RSTR		;
	uint32_t	Reserved2		;
	uint32_t	Reserved3		;
	uint32_t	AHB1ENR			;
	uint32_t	AHB2ENR			;
	uint32_t	AHB3ENR			;
	uint32_t	Reserved4		;
	uint32_t	APB1ENR			;
	uint32_t	APB2ENR			;
	uint32_t	Reserved5		;
	uint32_t	Reserved6		;
	uint32_t	AHB1LPENR		;
	uint32_t	AHB2LPENR		;
	uint32_t	AHB3LPENR		;
	uint32_t	Reserved7		;
	uint32_t	APB1LPENR		;
	uint32_t	APB2LPENR		;
	uint32_t	Reserved8		;
	uint32_t	Reserved9		;
	uint32_t	BDCR			;
	uint32_t	CSR				;
	uint32_t	Reserved10		;
	uint32_t	Reserved11		;
	uint32_t	SSCGR			;
	uint32_t	PLLI2SCFGR		;
}RCC_Reg_t;


#define RCC      ( (volatile RCC_Reg_t *) RCC_BASE_ADDRESS)

#define RCC_CLOCK_CR_HSI_RDY 		BIT_MASK_1
#define RCC_CLOCK_CR_HSE_RDY 		BIT_MASK_17
#define RCC_CLOCK_CR_PLL_RDY 		BIT_MASK_25
#define RCC_CLOCK_SW_PLL            BIT_MASK_

#define RCC_CFGR_SWS 		    	(BIT_MASK_2|BIT_MASK_3)
#define RCC_SYS_CLOCK_SWS_HSI		( (uint32_t)0x0U )
#define RCC_SYS_CLOCK_SWS_PLL  		( (uint32_t)0x8U )
#define RCC_SYS_CLOCK_SWS_HSE  		( (uint32_t)0x4U )

#define RCC_PLLCFGR_PLLSRC			BIT_MASK_22
#define RCC_PLLCFGR_PLLM			( BIT_MASK_0 | BIT_MASK_1 | BIT_MASK_2 | BIT_MASK_3 | BIT_MASK_4 | BIT_MASK_5 )
#define RCC_PLLCFGR_PLLN			( BIT_MASK_6 | BIT_MASK_7 | BIT_MASK_8 | BIT_MASK_9 | BIT_MASK_10 | BIT_MASK_11 | BIT_MASK_12 | BIT_MASK_13 | BIT_MASK_14)
#define RCC_PLLCFGR_PLLQ			( BIT_MASK_24 | BIT_MASK_25 | BIT_MASK_26 | BIT_MASK_27 )
#define RCC_PLLCFGR_PLLP			( BIT_MASK_16 | BIT_MASK_17 )

#define RCC_PLLCFGR_PLLN_OFFSET		( (uint32_t)0x6U )
#define RCC_PLLCFGR_PLLQ_OFFSET		( (uint32_t)24U )
#define RCC_PLLCFGR_PLLP_OFFSET  	( (uint32_t)0x16U )
#define RCC_CFGR_SW					(BIT_MASK_CLEAR_0 & BIT_MASK_CLEAR_1)


/*  MCO1_CLEAR*/
#define RCC_CFGR_MCO1				( BIT_MASK_CLEAR_21 & BIT_MASK_CLEAR_22 )
#define RCC_CFGR_MCO1_PRE			( BIT_MASK_CLEAR_24 & BIT_MASK_CLEAR_25 & BIT_MASK_CLEAR_26 )


/*  MCO2_CLEAR*/
#define RCC_CFGR_MCO2				( BIT_MASK_CLEAR_30 & BIT_MASK_CLEAR_31 )
#define RCC_CFGR_MCO2_PRE			( BIT_MASK_CLEAR_27 & BIT_MASK_CLEAR_28 & BIT_MASK_CLEAR_29 )


#define RCC_CFGR_HPRE				(  BIT_MASK_CLEAR_4 & BIT_MASK_CLEAR_5 & BIT_MASK_CLEAR_6 & BIT_MASK_CLEAR_7)

#define RCC_CFGR_PPRE1				(  BIT_MASK_CLEAR_10 & BIT_MASK_CLEAR_11 & BIT_MASK_CLEAR_12 )

#define RCC_CFGR_PPRE2				(  BIT_MASK_CLEAR_13 & BIT_MASK_CLEAR_14 & BIT_MASK_CLEAR_15 )

#define RCC_CFGR_RTCPRE				(  BIT_MASK_CLEAR_16 & BIT_MASK_CLEAR_17 & BIT_MASK_CLEAR_18 & BIT_MASK_CLEAR_19 & BIT_MASK_CLEAR_20 )

/*
 * uint32_t regTempData ;
	regTempData =
 */

/**
 * Turn the Selected clock ON
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_enableClock (uint32_t RCC_clock )
{
	uint32_t timeOut = 0xFFFFFFFF;
	if (RCC_clock == RCC_CLOCK_HSI || RCC_clock == RCC_CLOCK_HSE || RCC_clock == RCC_CLOCK_PLL ){

		RCC->CR |= RCC_clock;
	}
	if (RCC_clock == RCC_CLOCK_HSI){

		while( !(RCC->CR &  RCC_CLOCK_CR_HSI_RDY )){
			timeOut--;
			if (timeOut == 0  ){
				return RETURN_RCC_CLOCK_NOT_ALLOWED;
			}
		}
		return RETURN_SUCCESS;
	}
	if (RCC_clock == RCC_CLOCK_HSE){

		while(!( RCC->CR & RCC_CLOCK_CR_HSE_RDY   )){
			timeOut--;
			if (timeOut == 0  ){
				return RETURN_RCC_CLOCK_NOT_ALLOWED;
			}
		}
		return RETURN_SUCCESS;
	}
	if (RCC_clock == RCC_CLOCK_PLL){

		while( !(RCC->CR & RCC_CLOCK_CR_PLL_RDY  )){
			timeOut--;
			if (timeOut == 0  ){
				return RETURN_RCC_CLOCK_NOT_ALLOWED;
			}
		}
		return RETURN_SUCCESS;
	}

	return RETURN_ERROR_PARAM;

}

/**
 * Turn the Selected clock OFF
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_disableClock(uint32_t RCC_clock)
{

	if (RCC_clock == RCC_CLOCK_HSI){

		/*  Check if the HSI is the system clock*/
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_HSI){
			return RETURN_RCC_CLOCK_NOT_ALLOWED;
		}

		/*  Check if the PLL is the system clock
		 * and HSI is the PLL source
		 * */
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_PLL){
			if(!((RCC->PLLCFGR)& RCC_PLLCFGR_PLLSRC)){
				return RETURN_RCC_CLOCK_NOT_ALLOWED;
			}
		}

		(RCC->CR) &= (~(RCC_clock));
		return RETURN_SUCCESS;
	}



	if (RCC_clock == RCC_CLOCK_HSE){

		/*  Check if the HSE is the system clock*/
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_HSE){
			return RETURN_RCC_CLOCK_NOT_ALLOWED;
		}

		/*  Check if the PLL is the system clock
		 * and HSE is the PLL source
		 * */
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_PLL){
			if((RCC->PLLCFGR) & RCC_PLLCFGR_PLLSRC){
				return RETURN_RCC_CLOCK_NOT_ALLOWED;
			}
		}

		(RCC->CR) &= (~(RCC_clock));
		return RETURN_SUCCESS;

	}

	if (RCC_clock == RCC_CLOCK_PLL){
		/*
		 * Check if the PLL is the system clock
		 */
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_PLL){
			return RETURN_RCC_CLOCK_NOT_ALLOWED;
		}
		(RCC->CR) &= (~(RCC_clock));
		return RETURN_SUCCESS;
	}

	return RETURN_ERROR_PARAM;
}

uint32_t RCC_cfgPll(RCC_cfg_pll_t *RCC_cfg_pll)
{
	uint32_t PllClock = 0x00;
	uint32_t tempPLL_Reg = RCC ->PLLCFGR;
	/* check if the PLL is turned off */
	if ( RCC->CR & RCC_CLOCK_CR_PLL_RDY ){
		return RETURN_PLL_CFG_PLL_ON;
	}

	/* check the PLLsrc if it is HSE or HSI*/
	if ( !( RCC_cfg_pll -> RCC_cfgPllSrc ) ){
		/* check if HSI is Ready */
		if ( RCC->CR & RCC_CLOCK_CR_HSI_RDY){
			tempPLL_Reg &= (RCC_cfg_pll -> RCC_cfgPllSrc);
			PllClock = HSI_CLOCK;
		}
		else{
			return RETURN_RCC_CLOCK_NOT_RDY;
		}

	}
	else{
		/* check if HSE is Ready */
		if ( RCC->CR & RCC_CLOCK_CR_HSE_RDY){
			tempPLL_Reg |= (RCC_cfg_pll -> RCC_cfgPllSrc);
			PllClock = HSE_CLOCK;
		}
		else{
			return RETURN_RCC_CLOCK_NOT_RDY;
		}
	}

	/* check the range of M*/
	if( (RCC_cfg_pll -> RCC_cfgPllM) >= 2 && (RCC_cfg_pll -> RCC_cfgPllM) <= 63 && ((PllClock / RCC_cfg_pll -> RCC_cfgPllM) == 2 )){
		tempPLL_Reg |=  RCC_cfg_pll -> RCC_cfgPllM;
	}
	else {
		return RETURN_ERROR_PARAM;
	}

	/*  check the range of N*/
	if( (RCC_cfg_pll -> RCC_cfgPllN) >= 50 && (RCC_cfg_pll -> RCC_cfgPllM) <= 216){
		tempPLL_Reg |= ( RCC_cfg_pll -> RCC_cfgPllN << RCC_PLLCFGR_PLLN_OFFSET);
		PllClock = 2 * RCC_cfg_pll -> RCC_cfgPllN;
	}
	else{
		return RETURN_ERROR_PARAM;
	}

	/*  check the range of P */
	switch( RCC_cfg_pll -> RCC_cfgPllP )
	{
	case RCC_CFG_PLL_P_2:
		if ((PllClock / 2 ) <= 168){
			tempPLL_Reg |= RCC_CFG_PLL_P_2 ;

		}
		else{
			return RETURN_ERROR_PARAM;
		}
		break;
	case RCC_CFG_PLL_P_4:
		if ((PllClock / 4 ) <= 168){
			tempPLL_Reg |= RCC_CFG_PLL_P_4 ;

		}
		else{
			return RETURN_ERROR_PARAM;
		}
		break;
	case RCC_CFG_PLL_P_6:
		if ((PllClock / 6 ) <= 168){
			tempPLL_Reg |= RCC_CFG_PLL_P_6 ;

		}
		else{
			return RETURN_ERROR_PARAM;
		}
		break;
	case RCC_CFG_PLL_P_8:
		if ((PllClock / 8 ) <= 168){
			tempPLL_Reg |= RCC_CFG_PLL_P_8 ;

		}
		else{
			return RETURN_ERROR_PARAM;
		}
		break;

	default :
		return RETURN_ERROR_PARAM;
		break;
	}

	/*  check the range of N*/
	if( (RCC_cfg_pll -> RCC_cfgPllQ) >= 2 && (RCC_cfg_pll -> RCC_cfgPllQ) <= 15){
		tempPLL_Reg |= ( (RCC_cfg_pll -> RCC_cfgPllQ ) << RCC_PLLCFGR_PLLQ_OFFSET);
	}
	else{
		return RETURN_ERROR_PARAM;
	}
	RCC->PLLCFGR = tempPLL_Reg;
	return  RETURN_SUCCESS;
}


uint32_t RCC_selectSysClock(uint32_t RCC_sysClock)
{
	uint32_t SW_tempReg ;
	switch(RCC_sysClock)
	{
	case RCC_SYS_CLOCK_HSI:
		/* check if HSI is Ready */
		if ( RCC->CR & RCC_CLOCK_CR_HSI_RDY){
			SW_tempReg = (RCC->CFGR & RCC_CFGR_SW);
			SW_tempReg |= RCC_SYS_CLOCK_HSI;
			RCC->CFGR = SW_tempReg;
		}
		/*  Check if the HSI is the system clock*/
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_HSI){
			return RETURN_SUCCESS;
		}
		else{
			return RETURN_RCC_CLOCK_NOT_RDY;
		}
		break;
	case RCC_SYS_CLOCK_HSE:
		/* check if HSI is Ready */
		if ( RCC->CR & RCC_CLOCK_CR_HSE_RDY){
			SW_tempReg = (RCC->CFGR & RCC_CFGR_SW);
			SW_tempReg |= RCC_SYS_CLOCK_HSE;
			RCC->CFGR = SW_tempReg;

		}
		/*  Check if the HSE is the system clock*/
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_HSE){
			return RETURN_SUCCESS;
		}
		else{
			return RETURN_RCC_CLOCK_NOT_RDY;
		}
		break;
	case RCC_SYS_CLOCK_PLL:
		/* check if HSI is Ready */
		if ( RCC->CR & RCC_CLOCK_CR_PLL_RDY){
			SW_tempReg = (RCC->CFGR & RCC_CFGR_SW);
			SW_tempReg |= RCC_SYS_CLOCK_PLL;
			RCC->CFGR = SW_tempReg;

		}
		/*  Check if the PLL is the system clock */
		if((RCC->CFGR & RCC_CFGR_SWS) == RCC_SYS_CLOCK_SWS_PLL){
			return RETURN_SUCCESS;
		}
		else{
			return RETURN_RCC_CLOCK_NOT_RDY;
		}
		break;
	default :
		return RETURN_ERROR_PARAM;
		break;
	}

}


uint32_t RCC_getSysClockFrequency(uint32_t *returnFreq)
{
	uint32_t PLLN = 0x00;
	uint32_t PLLP = 0x00;
	uint32_t PLLM = 0x00;
	switch(RCC->CFGR & RCC_CFGR_SWS)
	{
	case RCC_SYS_CLOCK_SWS_HSI:
		*returnFreq = HSI_CLOCK ;
		return RETURN_SUCCESS;
		break;

	case RCC_SYS_CLOCK_SWS_HSE:
		*returnFreq = HSE_CLOCK ;
		return RETURN_SUCCESS;
		break;

	case RCC_SYS_CLOCK_SWS_PLL:
		PLLN = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_OFFSET;
		switch( (RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_OFFSET)
		{
		case RCC_CFG_PLL_P_2:
			PLLP = 2;
			break;
		case RCC_CFG_PLL_P_6:
			PLLP = 6;
			break;
		case RCC_CFG_PLL_P_8:
			PLLP = 8;
			break;
		case RCC_CFG_PLL_P_4:
			PLLP = 4;
			break;
		}

		PLLM = (RCC-> PLLCFGR & RCC_PLLCFGR_PLLM);
		if(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC){

			*returnFreq = (HSE_CLOCK * PLLN)/(PLLP * PLLM);
		}
		else{
			*returnFreq = (HSI_CLOCK * PLLN)/(PLLP * PLLM);
		}
		break;

		default :
			return RETURN_ERROR_PARAM;
			break;
	}
}

uint32_t RCC_AHB1_status(uint32_t RCC_AHB1, uint32_t RCC_periState)
{
	uint32_t AHB1_tempReg = RCC -> AHB1ENR;

	if(RCC_periState){
		AHB1_tempReg |= RCC_AHB1;
	}
	else{
		AHB1_tempReg &= ~(RCC_AHB1);
	}
	RCC -> AHB1ENR = AHB1_tempReg;
	return RETURN_SUCCESS;
}

uint32_t RCC_AHB2_status(uint32_t RCC_AHB2, uint32_t RCC_periState)
{
	uint32_t AHB2_tempReg = RCC -> AHB2ENR;

	if(RCC_periState){
		AHB2_tempReg |= RCC_AHB2;
	}
	else{
		AHB2_tempReg &= ~(RCC_AHB2);
	}
	RCC -> AHB2ENR = AHB2_tempReg;
	return RETURN_SUCCESS;
}

uint32_t RCC_APB1_status(uint32_t RCC_APB1, uint32_t RCC_periState)
{
	uint32_t APB1_tempReg = RCC -> APB1ENR;

	if(RCC_periState){
		APB1_tempReg |= RCC_APB1;
	}
	else{
		APB1_tempReg &= ~(RCC_APB1);
	}
	RCC -> APB1ENR = APB1_tempReg;
	return RETURN_SUCCESS;
}

uint32_t RCC_APB2_status(uint32_t RCC_APB2, uint32_t RCC_periState)
{
	uint32_t APB2_tempReg = RCC -> APB2ENR;

	if(RCC_periState){
		APB2_tempReg |= RCC_APB2;
	}
	else{
		APB2_tempReg &= ~(RCC_APB2);
	}
	RCC -> APB1ENR = APB2_tempReg;
	return RETURN_SUCCESS;
}


uint32_t RCC_setMCO1_Clock(uint32_t RCC_MCO1_out, uint32_t RCC_MCO1_prescaler)
{
	uint32_t MCO_tempReg ;
	if ( ( (RCC_MCO1_out == RCC_MCO1_HSI	 ) ||
			(RCC_MCO1_out == RCC_MCO1_LSE	 ) ||
			(RCC_MCO1_out == RCC_MCO1_HSE	 ) ||
			(RCC_MCO1_out == RCC_MCO1_PLL	 ) )&&
			(       (RCC_MCO1_prescaler == RCC_MCO1_PRE_OFF) ||
					(RCC_MCO1_prescaler == RCC_MCO1_PRE_2	 )||
					(RCC_MCO1_prescaler == RCC_MCO1_PRE_3	 )||
					(RCC_MCO1_prescaler == RCC_MCO1_PRE_4	 )||
					(RCC_MCO1_prescaler == RCC_MCO1_PRE_5	 ) ))
	{
		MCO_tempReg &= ( RCC_CFGR_MCO1 & RCC_CFGR_MCO1_PRE );
		MCO_tempReg |= ( RCC_MCO1_out | RCC_CFGR_MCO1_PRE );
		RCC-> CFGR = MCO_tempReg;
		return RETURN_SUCCESS;
	}
	else{
		return RETURN_ERROR_PARAM;
	}
}


uint32_t RCC_setMCO2_Clock(uint32_t RCC_MCO2_out, uint32_t RCC_MCO2_prescaler)
{
	uint32_t MCO_tempReg ;
	if ( (  (RCC_MCO2_out == RCC_MCO2_PLLI2S	 ) ||
			(RCC_MCO2_out == RCC_MCO2_SYSCLK	 ) ||
			(RCC_MCO2_out == RCC_MCO2_HSE	 ) ||
			(RCC_MCO2_out == RCC_MCO2_PLL	 ) )&&
			( 		(RCC_MCO2_prescaler == RCC_MCO2_PRE_OFF) ||
					(RCC_MCO2_prescaler == RCC_MCO2_PRE_2	 )||
					(RCC_MCO2_prescaler == RCC_MCO2_PRE_3	 )||
					(RCC_MCO2_prescaler == RCC_MCO2_PRE_4	 )||
					(RCC_MCO2_prescaler == RCC_MCO2_PRE_5	 ) ))
	{
		MCO_tempReg &= ( RCC_CFGR_MCO2 & RCC_CFGR_MCO2_PRE );
		MCO_tempReg |= ( RCC_MCO2_out | RCC_CFGR_MCO2_PRE );
		RCC-> CFGR = MCO_tempReg;
		return RETURN_SUCCESS;
	}
	else{
		return RETURN_ERROR_PARAM;
	}
}


uint32_t RCC_setHPRE(uint32_t RCC_HPRE)
{
	if(     ( RCC_HPRE != RCC_HPRE_OFF	) ||
			( RCC_HPRE != RCC_HPRE_2	) ||
			( RCC_HPRE != RCC_HPRE_4	) ||
			( RCC_HPRE != RCC_HPRE_8	) ||
			( RCC_HPRE != RCC_HPRE_16	) ||
			( RCC_HPRE != RCC_HPRE_64	) ||
			( RCC_HPRE != RCC_HPRE_128  ) ||
			( RCC_HPRE != RCC_HPRE_256  ) ||
			( RCC_HPRE != RCC_HPRE_512  )
	)
	{
		return RETURN_ERROR_PARAM;

	}

	uint32_t HPRE_tempReg =  RCC->CFGR ;
	HPRE_tempReg &= RCC_CFGR_HPRE;
	HPRE_tempReg |= RCC_HPRE;
	RCC->CFGR = HPRE_tempReg;
	return RETURN_SUCCESS;

}


uint32_t RCC_getHPRE(uint32_t * prescaler)
{
	uint32_t HPRE_tempReg =  RCC->CFGR ;

	switch( HPRE_tempReg & (~RCC_CFGR_HPRE) )
	{
	case RCC_HPRE_OFF:
		* prescaler = 1;
		break;
	case RCC_HPRE_2:
		* prescaler = 2;
		break;
	case RCC_HPRE_4:
		* prescaler = 4;
		break;
	case RCC_HPRE_8:
		* prescaler = 8;
		break;
	case RCC_HPRE_16:
		* prescaler = 16;
		break;
	case RCC_HPRE_64:
		* prescaler = 64;
		break;
	case RCC_HPRE_128:
		* prescaler = 128;
		break;
	case RCC_HPRE_256:
		* prescaler = 256;
		break;
	case RCC_HPRE_512:
		* prescaler = 512;
		break;
	default:
		return RETURN_RUNNING_TIME_ERROR;
		break;
	}
	return RETURN_SUCCESS;
}



uint32_t RCC_setHPRE1(uint32_t RCC_PPRE1)
{
	if (
			( RCC_PPRE1 != RCC_PPRE1_1	) ||
			( RCC_PPRE1 != RCC_PPRE1_2	) ||
			( RCC_PPRE1 != RCC_PPRE1_4	) ||
			( RCC_PPRE1 != RCC_PPRE1_8	) ||
			( RCC_PPRE1!= RCC_PPRE1_16  )
	)
	{
		return RETURN_ERROR_PARAM;
	}

	uint32_t HPRE_tempReg =  RCC->CFGR ;
	HPRE_tempReg &= RCC_CFGR_PPRE1;
	HPRE_tempReg |= RCC_PPRE1;
	RCC->CFGR = HPRE_tempReg;
	return RETURN_SUCCESS;

}



uint32_t RCC_setHPRE2(uint32_t RCC_PPRE2)
{
	if (
			( RCC_PPRE2 != RCC_PPRE2_1	) ||
			( RCC_PPRE2 != RCC_PPRE2_2	) ||
			( RCC_PPRE2 != RCC_PPRE2_4	) ||
			( RCC_PPRE2 != RCC_PPRE2_8	) ||
			( RCC_PPRE2!=  RCC_PPRE2_16  )
	)
	{
		return RETURN_ERROR_PARAM;
	}

	uint32_t HPRE_tempReg =  RCC->CFGR ;
	HPRE_tempReg &= RCC_CFGR_PPRE2;
	HPRE_tempReg |= RCC_PPRE2;
	RCC->CFGR = HPRE_tempReg;
	return RETURN_SUCCESS;

}




uint32_t RCC_setRTCPRE(uint32_t RCC_RTCPRE)
{
	if ( ( RCC_RTCPRE > 2 ) && ( RCC_RTCPRE < 32 ) )
	{
		uint32_t HPRE_tempReg =  RCC->CFGR ;
		HPRE_tempReg &= RCC_CFGR_RTCPRE;
		HPRE_tempReg |= RCC_RTCPRE;
		RCC->CFGR = HPRE_tempReg;
		return RETURN_SUCCESS;
	}
	else
	{
		return RETURN_ERROR_PARAM;
	}
}

uint32_t RCC_setSysClock(uint32_t RCC_Clock)
{
	/* Check if the coming clock is in the range of the VSO */
	if( (RCC_Clock < 50) || (RCC_Clock > 100) )
	{
		return RETURN_ERROR_PARAM;
	}
	/* switch to HSI system clock */
	if (RCC_selectSysClock( RCC_SYS_CLOCK_HSI))
	{
		return RETURN_RCC_CLOCK_NOT_ALLOWED;
	}

	/* Disable PLL to configure it */
	if (RCC_disableClock(RCC_CLOCK_PLL ) )
	{
		return RETURN_RCC_CLOCK_NOT_ALLOWED;
	}

	RCC_cfg_pll_t setPLL = {
			.RCC_cfgPllSrc = RCC_CFG_PLL_SRC_HSE,
			.RCC_cfgPllM = 4,
			.RCC_cfgPllN = RCC_Clock,
			.RCC_cfgPllP = RCC_CFG_PLL_P_2,
			.RCC_cfgPllQ = 6
	};

	/* Configure PLL */
	if ( RCC_cfgPll(&setPLL) )
	{
		return RETURN_RCC_CLOCK_NOT_ALLOWED;
	}


	/* Enable PLL */
	if (RCC_enableClock(RCC_CLOCK_PLL ) )
	{
		return RETURN_RCC_CLOCK_NOT_ALLOWED;
	}

	/* switch to PLL as system clock */
	if (RCC_selectSysClock( RCC_SYS_CLOCK_PLL))
	{
		return RETURN_RCC_CLOCK_NOT_ALLOWED;
	}

	return RETURN_SUCCESS;
}


