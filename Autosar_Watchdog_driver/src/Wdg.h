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


#define WDG_COUNTER_CLOCK_DIV_1      (uint8)( 0x00 )
#define WDG_COUNTER_CLOCK_DIV_2      (uint8)( BIT7 )
#define WDG_COUNTER_CLOCK_DIV_4      (uint8)( BIT8 )
#define WDG_COUNTER_CLOCK_DIV_8      (uint8)( BIT7 | BIT8)


/***************************
 * Function Description :  Switches the watch dog into the mode Mode.
 *
 * Parameters : WdgIf_ModeType Mode
 *
 * Return : Std_ReturnType.
 *
 ***************************/
Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode);

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
 * Covers : [SWS_Wdg_00174]
 *
 *
 ***************************/
void Wdg_GetVersionInfo( Std_VersionInfoType* versioninfo );

#endif /* WDG_H_ */
