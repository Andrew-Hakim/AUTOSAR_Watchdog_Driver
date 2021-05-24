/*
 * Wdg.c
 *
 *  Created on: Apr 22, 2021
 *      Author: Andrew
 */

#include "Wdg.h"
#include "Wdg_Cfg.h"
#include "SchM_Wdg.h"
#include "Wdg_Registers.h"
#include "Wdg_Lcfg.h"

/* Version information of the module */
#define MODEL_ID		3
#define VENDOR_ID		2
#define MAJOR_VERSION   2
#define MINOR_VERSION   1
#define PATCH_VERSION   2


/*next define for select mode func*/
#define  WDT_CR_REG_RESET			0x0000007F
#define WD_WDGTB_MASK 				0x00000180
#define WD_WDGT_CLEAR_MASK 			~0x0000003F
#define WDGTB_RESET 				0b001111111
#define WDGA_SET					0b10000000
#define WdgMaxTimeout					69


void Wdg_Init( const Wdg_ConfigType* ConfigPtr )
{

	uint32  WWDG_CFR_temp = (WWDG_REG->WWDG_CFR);
	WWDG_CFR_temp = ConfigPtr->WdgWindowValue;
	(WWDG_REG->WWDG_CFR) |= WWDG_CFR_temp;
	(WWDG_REG->WWDG_CR)  = ( ConfigPtr->WdgCounter | WDGA_SET );
}


void Wdg_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
	versioninfo->moduleID = MODEL_ID;
	versioninfo->sw_major_version = MAJOR_VERSION;
	versioninfo->sw_minor_version = MINOR_VERSION;
	versioninfo->sw_patch_version = PATCH_VERSION;
	versioninfo->vendorID = VENDOR_ID ;
}




Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode){


	if(WDGIF_OFF_MODE==Mode){
		/*code*/
		WWDG_REG->WWDG_CR &= BIT7_CLEAR;	//WDGA=0;	to disable the watch dog = turn it off
	}

#if     WD_SLOW_MODE == WD_MODE_IS_AVAILABE
	/*speed of the slow mode should be within 5ms*/
	/*so should adjust the rcc to get the reset speed */
	// RCC_SPEED
	else if(WDGIF_SLOW_MODE==Mode){
		/*code*/
		WWDG_REG->WWDG_CR |=  WDT_CR_REG_RESET;
		WWDG_REG->WWDG_CFR |= BIT8 | BIT7;	// prescaler for every dec is 8 so dec every 4096 & 2 power (8) = WDGTB // the slowest & longest decrement

	}
#endif

#if     WD_FAST_MODE == WD_MODE_IS_AVAILABE
	/*speed of the fast mode should be within 20ms*/
	/*so should adjust the rcc to get the reset speed */
	/*rcc reg to enable windowed WD is RCC_APB1ENR*/
	/*if we work with 168 MHZ as SYSCLK then AHB-PRESC= 1 and APH1-PRESC=1 */
	/*	decrement 1 = freq /dec value = 168 MHZ / 4096 = 41015.5 hz
	 * time for single decrement = 1/41015.5 hz = 24 Microsec
	 * to get 20 ms i need to decrement
	 * equation
	 * ---------
	 * decrement value  = desired time / tick time = 20ms/24 Msec = 0.00020 / 0.00000024  = 833
	 * 833 in decemel
	 * 833 decemal = 341 in hex need to lower the freq to fit our watch dog
	 *	to get 20 ms
	 * */

	/*use prescaler = 8 to make the speed of the WD is 21MHz   168/8 = 21 MHZ (mega HZ)
	 * decrement 1 = freq /dec value = 42 MHZ / 4096 =  5127 hz
	 * time for single decrement = 1/5127 hz = 195 Microsec
	 * decrement value  = desired time / tick time = 20ms/195 Msec = 0.00020 / 0.00000195  = 102 decemal= 0x66 hexa
	 *
	 * */
	else if(WDGIF_FAST_MODE==Mode){
		/*code*/
		WWDG_REG->WWDG_CR |=  WDT_CR_REG_RESET;
		WWDG_REG->WWDG_CFR &= BIT8_CLEAR | BIT7_CLEAR;	// prescaler for every dec is 1 so dec every 4096 & 2 power (1) = WDGTB, div by 1

	}
#endif
	else {
		/*return error or wrong parameter*/
		return 1;   // error E_NOK
	}
	return 0;	// return E_OK
}




/**************************************************************************************************************
 * Public Function [SWS_Wdg_00155]: Wdg_SetTriggerCondition
 * Description: This function is used to set the timeout value for the trigger counter
 * Input Parameters:
 * 					 -uint16 timeout : the timeout value in ms
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Covers:SWS_Wdg_00136 ,SWS_Wdg_00138 ,SWS_Wdg_00140
 *
 * NOTE: This Function doesn't apply this AUTOSAR Requirement --> SWS_Wdg_00139
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void Wdg_SetTriggerCondition(uint16 timeout)
{
	/*
	 * tWWDG=tPCLK1 * 4096 * 2 ^(WDGTB[1:0]) * (T[5:0]+1)
	 * T[5:0] =( tWWDG/(tPCLK1 * 4096 * 2 ^(WDGTB[1:0])) )-1
	 * --> get the tPCLK1 = (1000/WD_PCLK_MHZ) ms
	 * --> get 2^timebase = (1 << timebase)
	 * */
	uint8 timebase ;
	uint16 Loc_u16CountDownVal;
	/*I Couldn't clear the T bits then OR the register with the new value,
	 * because clearing them does an instant reset */
	uint32 Loc_u32WDCR = WWDG_REG->WWDG_CR ;

	if (timeout >= WdgMaxTimeout)
	{
		//Det_Error(WDG_E_PARAM_TIMEOUT);
		return ;
	}
	else if (timeout == 0 )
	{
		/*if the timeout equals do an instant reset */
		Loc_u32WDCR &= WD_WDGT_CLEAR_MASK ;
	}
	else
	{
		/*if not calculate the T[5:0] to be set in the CR register from the equation */
		timebase = (WWDG_REG->WWDG_CFR & WD_WDGTB_MASK) >> 7;
		Loc_u16CountDownVal= (timeout/((1000.0/WD_PCLK_MHZ) * 4096 * (1 << timebase))) - 1;
		Loc_u32WDCR &= WD_WDGT_CLEAR_MASK ;
		Loc_u32WDCR |= Loc_u16CountDownVal & 0x003F;
	}
		WWDG_REG->WWDG_CR = Loc_u32WDCR;

}











