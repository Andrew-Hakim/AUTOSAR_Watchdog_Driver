/*
 * Wdglf_Types.h
 *
 *  Created on: Apr 22, 2021
 *      Author: Andrew
 */

#ifndef WDGLF_TYPES_H_
#define WDGLF_TYPES_H_

#include "Std_Types.h"

/*
 *	Used for pointers to structures holding configuration data provided to the Wdg
 *	module initialization routine for configuration of the module and watchdog
 *	hardware
 *
 *	Example :
*				Wdg_ConfigType WdgCongfiguration = {
					.WdgCounter = 200,
					.WdgWindowValue =100,
					.WdgTimerBase = WDG_COUNTER_CLOCK_DIV_2,
					.WdgMode = WDGIF_FAST_MODE
				};
 *
 * */

typedef enum{
	WDGIF_OFF_MODE,
	WDGIF_SLOW_MODE,
	WDGIF_FAST_MODE
}WdgIf_ModeType;


typedef struct
{
	uint8 WdgCounter;
	uint8 WdgWindowValue;
	uint8 WdgTimerBase;
}Wdg_ConfigType;



#endif /* WDGLF_TYPES_H_ */
