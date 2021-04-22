/*
 * Wdg.h
 *
 *  Created on: Apr 22, 2021
 *      Author: Andrew
 */

#ifndef WDG_H_
#define WDG_H_

#include "Bits.h"
#include "Wdglf_Types.h"
#include "Wdg_Cfg.h"

/*
#define     WDGIF_OFF_MODE      1
#define     WDGIF_SLOW_MODE     2
#define     WDGIF_FAST_MODE     3
*/


#define WDG_COUNTER_CLOCK_DIV_1      (uint8_t)( 0x00 )
#define WDG_COUNTER_CLOCK_DIV_2      (uint8_t)( BIT7 )
#define WDG_COUNTER_CLOCK_DIV_4      (uint8_t)( BIT8 )
#define WDG_COUNTER_CLOCK_DIV_8      (uint8_t)( BIT7 | BIT8)


/***************************
 * Function Description :  Switches the watchdog into the mode Mode.
 *
 * Parameters : WdgIf_ModeType Mode
 *
 * Return : Std_ReturnType.
 *
 ***************************/
Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode);

/**************************************************************************************************************
 * Public Function: Wdg_SetTriggerCondition
 * Description: This function is used to set the timeout value for the watch dog timer.
 * Input Parameters:
 * 					 -uint16 timeout: the timeout in milliseconds.
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void Wdg_SetTriggerCondition(uint16 timeout);



/***************************
 * Function Description : Initializes the module.
 *
 * Parameters : pointer to Wdg_ConfigType.
 *
 * Return : None.
 *
 * Covers :  [SWS_Wdg_00001], [SWS_Wdg_00100], [SWS_Wdg_00101], [SWS_Wdg_00173],
 * 			 [SWS_Wdg_00090].
 *
 *Not Covered : [SWS_Wdg_00025], [SWS_Wdg_00019].
 ***************************/
void Wdg_Init( const Wdg_ConfigType* ConfigPtr );




/***************************
 * Function Description : Returns the version information of the module.
 *
 * Parameters : Std_VersionInfoType.
 *
 * Return : None.
 *
 * Covers :
 *
 *
 ***************************/
void Wdg_GetVersionInfo( Std_VersionInfoType* versioninfo );

#endif /* WDG_H_ */
