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

/*next define for select mode func*/
#define  WDT_CR_REG_RESET			0x0000007F


#define WDGTB_RESET 		0b001111111
#define WDGA_SET			0b10000000

void Wdg_Init( const Wdg_ConfigType* ConfigPtr )
{
	uint32  WWDG_CFR_temp = (WWDG_REG->WWDG_CFR);
	WWDG_CFR_temp = ConfigPtr->WdgWindowValue;
	WWDG_CFR_temp &= WDGTB_RESET;
	WWDG_CFR_temp |= ConfigPtr->WdgTimerBase;
	(WWDG_REG->WWDG_CFR) = WWDG_CFR_temp;
	(WWDG_REG->WWDG_CR)  = ( ConfigPtr->WdgCounter | WDGA_SET );
}


void Wdg_GetVersionInfo( Std_VersionInfoType* versioninfo )
{

}




Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode){

#if     WD_OFF_MODE  == WD_MODE_IS_AVAILABE

    if(WDGIF_OFF_MODE==Mode){
    /*code*/
    	WWDG_REG->WWDG_CR &= BIT7_CLEAR;	//WDGA=0;	to disable the watch dog = turn it off
    }
#endif

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


