/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "../../lib/src/Std_Types.h"
#include "../../lib/src/Bit_Mask.h"
#include "../../lib/src/errorCode.h"
#include "RCC.h"
#include "Wdg.h"
// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

extern  Wdg_ConfigType User_WdgCongfiguration;

int main(int argc, char* argv[])
{
	uint32_t count = 0;
	uint32_t Loc_u32testvar=0;
	RCC_APB1_status(RCC_APB1_WWDG,RCC_PERI_STATE_ENABLE);
	RCC_setHPRE1(RCC_PPRE1_4);


	Wdg_SetMode(WDGIF_SLOW_MODE);
//	Wdg_SetMode(WDGIF_FAST_MODE);
	Wdg_Init(&User_WdgCongfiguration);
	Wdg_SetTriggerCondition(10);



	trace_printf("The start of execution \n ");
	if(Loc_u32testvar == 0)
	{
		/*infinite loop to reset the  watchdog timer  */
		while(1){
			count ++ ;
						trace_printf("counter : %i \n", count);
		}
	}
	else {
		/*This code will never reset because the watchdog is always updated*/
		while (1)
		{
			count ++ ;
			trace_printf("counter : %i \n", count);
			Wdg_SetTriggerCondition(50);
		}
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
