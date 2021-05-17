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
