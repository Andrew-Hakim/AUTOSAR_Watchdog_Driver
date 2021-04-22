/*
 * Wdg.h
 *
 *  Created on: Apr 22, 2021
 *      Author: Andrew
 */

#ifndef WDG_H_
#define WDG_H_

#include "Wdglf_Types.h"
#include "Wdg_Cfg.h"

/*
#define     WDGIF_OFF_MODE      1
#define     WDGIF_SLOW_MODE     2
#define     WDGIF_FAST_MODE     3
*/

typedef enum{
WDGIF_OFF_MODE,
WDGIF_SLOW_MODE,
WDGIF_FAST_MODE
}WdgIf_ModeType;


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



#endif /* WDG_H_ */
