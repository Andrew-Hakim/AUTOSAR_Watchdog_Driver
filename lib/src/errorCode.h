/*
 * errorCode.h
 *
 *  Created on: Feb 12, 2021
 *      Author: andrew
 */

#ifndef ERRORCODE_H_
#define ERRORCODE_H_


/* General Error codes */
#define RETURN_SUCCESS  						((uint32_t)0x0)
#define RETURN_ERROR_PARAM       				((uint32_t)0x20)
#define RETURN_REG_NOT_UPDATED					((uint32_t)0x30)
#define RETURN_RUNNING_TIME_ERROR				((uint32_t)0x40)
/*  RCC Error codes */
#define RETURN_RCC_CLOCK_NOT_ALLOWED			((uint32_t)0x300)
#define RETURN_PLL_CFG_PLL_ON					((uint32_t)0x400)
#define RETURN_RCC_CLOCK_NOT_RDY				((uint32_t)0x500)



#endif /* ERRORCODE_H_ */
