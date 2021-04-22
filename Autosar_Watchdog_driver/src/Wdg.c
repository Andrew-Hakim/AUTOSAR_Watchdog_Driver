/*
 * Wdg.c
 *
 *  Created on: Apr 22, 2021
 *      Author: Andrew
 */

#include "Wdg.h"
#include "Wdg_Cfg.h"
#include "SchM_Wdg.h"



Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode)
{

#if     WD_OFF_MODE  == WD_MODE_IS_AVAILABE

	if(WDGIF_OFF_MODE==Mode)
	{
		/*code*/
		Reg->WWDG_CR &= BIT7_CLEAR;	//WDGA=0;	to disable the watch dog = turn it off
	}
#endif

#if     WD_SLOW_MODE == WD_MODE_IS_AVAILABE
	else if(WDGIF_SLOW_MODE==Mode)
	{
		/*code*/
		Reg->WWDG_CR |= BIT7;		//WDGA=1; enable it 1st
		Reg->WWDG_CFR |= BIT8 | BIT7;	// prescaler for every dec is 8 so dec every 4096 & 2 power (8) = WDGTB // the slowest & longest decrement
	}
#endif

#if     WD_FAST_MODE == WD_MODE_IS_AVAILABE
	else if(WDGIF_FAST_MODE==Mode)
	{
		/*code*/
		Reg->WWDG_CR |= BIT7;				//WDGA=1; enable it 1st
		Reg->WWDG_CFR &= (BIT8_CLEAR & BIT7_CLEAR);	// prescaler for every dec is 1 so dec every 4096 & 2 power (1) = WDGTB
	}
#endif
	else {
		/*return error or wrong parameter*/
		return 1;   // error
	}
	return 0;
}
