/*
 * Wdg.c
 *
 *  Created on: Apr 22, 2021
 *      Author: Andrew
 */

#include "Wdg.h"
#include "Wdg_Cfg.h"
#include "SchM_Wdg.h"



Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode){

#if     WD_OFF_MODE  == WD_MODE_IS_AVAILABE

    if(WDGIF_OFF_MODE==WdgIf_ModeType){
    /*code*/
    }
#endif

#if     WD_SLOW_MODE == WD_MODE_IS_AVAILABE
    else if(WDGIF_SLOW_MODE==WdgIf_ModeType){
    /*code*/
    }
#endif

#if     WD_FAST_MODE == WD_MODE_IS_AVAILABE
    else if(WDGIF_FAST_MODE==WdgIf_ModeType){
    /*code*/
    }
#endif
    else {
    /*return error or wrong parameter*/
    return 1;   // error
    }
return 0;
}
