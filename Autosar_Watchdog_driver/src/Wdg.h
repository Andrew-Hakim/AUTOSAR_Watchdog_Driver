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

typedef enum{
WDGIF_OFF_MODE,
WDGIF_SLOW_MODE,
WDGIF_FAST_MODE
}WdgIf_ModeType;

#endif /* WDG_H_ */
