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
	Used for pointers to structures holding configuration data provided to the Wdg
	module initialization routine for configuration of the module and watchdog
	hardware
 */
typedef struct
{
	uint8_t WdgCounter;
	uint8_t WdgWindowValue;
	uint8_t WdgTimerBase;

}Wdg_ConfigType;


typedef enum{
	WDGIF_OFF_MODE,
	WDGIF_SLOW_MODE,
	WDGIF_FAST_MODE
}WdgIf_ModeType;

#endif /* WDGLF_TYPES_H_ */
