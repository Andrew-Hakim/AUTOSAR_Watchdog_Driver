/*
 * Wdg_Registers.h
 *
 *  Created on: May 17, 2021
 *      Author: Andrew
 */

#ifndef WDG_REGISTERS_H_
#define WDG_REGISTERS_H_


typedef struct
{
	uint32 WWDG_CR;
	uint32 WWDG_CFR;
	uint32 WWDG_SR;
}WWDG_registers;


#define WWDG_REG     ((volatile WWDG_registers *)0x40002C00)

#endif /* WDG_REGISTERS_H_ */
