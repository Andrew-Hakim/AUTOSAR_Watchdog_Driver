/*
 * RCC.h
 *
 *  Created on: Jan 29, 2021
 *      Author: andrew
 */

#ifndef RCC_H_
#define RCC_H_


// Clocks in the system
#define RCC_CLOCK_HSI	    			BIT_MASK_0
#define RCC_CLOCK_HSE					BIT_MASK_16
#define RCC_CLOCK_PLL					BIT_MASK_24

#define RCC_SYS_CLOCK_HSI				((uint32_t)0x00U)
#define RCC_SYS_CLOCK_HSE				( BIT_MASK_0 )
#define RCC_SYS_CLOCK_PLL				( BIT_MASK_1 )

// PLL configuration
#define RCC_CFG_PLL_SRC_HSI				BIT_MASK_CLEAR_22
#define RCC_CFG_PLL_SRC_HSE				BIT_MASK_22
#define RCC_CFG_PLL_P_2					((uint32_t)0x0U)
#define RCC_CFG_PLL_P_4					BIT_MASK_16
#define RCC_CFG_PLL_P_6					BIT_MASK_17
#define RCC_CFG_PLL_P_8					( BIT_MASK_17 | BIT_MASK_16 )

// struct type to hold PLL configuration
typedef struct{
	uint32_t RCC_cfgPllSrc;
	uint32_t RCC_cfgPllM;
	uint32_t RCC_cfgPllN;
	uint32_t RCC_cfgPllP;
	uint32_t RCC_cfgPllQ;
}RCC_cfg_pll_t;


// Peripherals status (ON/OFF)
#define RCC_PERI_STATE_ENABLE 			((uint32_t)0x01U)
#define RCC_PERI_STATE_DISABLE 			((uint32_t)0x00U)

//RCC_AHB1ENR
#define RCC_AHB1_GPIOA					BIT_MASK_0
#define RCC_AHB1_GPIOB					BIT_MASK_1
#define RCC_AHB1_GPIOC					BIT_MASK_2
#define RCC_AHB1_GPIOD					BIT_MASK_3
#define RCC_AHB1_GPIOE					BIT_MASK_4
#define RCC_AHB1_GPIOF					BIT_MASK_5
#define RCC_AHB1_GPIOG					BIT_MASK_6
#define RCC_AHB1_GPIOH					BIT_MASK_7
#define RCC_AHB1_CRC					BIT_MASK_12
#define RCC_AHB1_BKPSRAM				BIT_MASK_18
#define RCC_AHB1_CCMDATARAM				BIT_MASK_20
#define RCC_AHB1_DMA1			     	BIT_MASK_21
#define RCC_AHB1_DMA2					BIT_MASK_22
#define RCC_AHB1_ETHMAC	     		    BIT_MASK_25
#define RCC_AHB1_ETHMACTX			    BIT_MASK_26
#define RCC_AHB1_ETHMACRX			    BIT_MASK_27
#define RCC_AHB1_ETHMACPTP				BIT_MASK_28
#define RCC_AHB1_OTGH				    BIT_MASK_29
#define RCC_AHB1_OTGHSULPIEN			BIT_MASK_30



//AHB2 peripheral (RCC_AHB2EBR)
#define  RCC_AHB2_DCMI 					BIT_MASK_0
#define  RCC_AHB2_CRYP					BIT_MASK_4
#define  RCC_AHB2_HASH					BIT_MASK_5
#define  RCC_AHB2_RNG					BIT_MASK_6
#define  RCC_AHB2_OTGFS					BIT_MASK_7


//APB1 peripheral (RCC_APB1EBR)
#define  RCC_APB1_TIM2LP				BIT_MASK_0
#define  RCC_APB1_TIM3LP				BIT_MASK_1
#define  RCC_APB1_TIM4LP				BIT_MASK_2
#define  RCC_APB1_TIM5LP				BIT_MASK_3
#define  RCC_APB1_TIM6LP				BIT_MASK_4
#define  RCC_APB1_TIM7LP				BIT_MASK_5
#define  RCC_APB1_TIM12LP				BIT_MASK_6
#define  RCC_APB1_TIM13LP				BIT_MASK_7
#define  RCC_APB1_TIM14LP				BIT_MASK_8
#define  RCC_APB1_WWDG		     	    BIT_MASK_11
#define  RCC_APB1_SPI2LP			 	BIT_MASK_14
#define  RCC_APB1_SPI3LP				BIT_MASK_15
#define  RCC_APB1_USART2				BIT_MASK_17
#define  RCC_APB1_USART3				BIT_MASK_18
#define  RCC_APB1_USART4			    BIT_MASK_19
#define  RCC_APB1_USART5		        BIT_MASK_20
#define  RCC_APB1_I2C1			        BIT_MASK_21
#define  RCC_APB1_I2C2			 		BIT_MASK_22
#define  RCC_APB1_I2C3 		           	BIT_MASK_23
#define  RCC_APB1_CAN1LP				BIT_MASK_25
#define  RCC_APB1_CAN2LP				BIT_MASK_26
#define  RCC_APB1_PWRLP			       	BIT_MASK_28
#define  RCC_APB1_DACLP			        BIT_MASK_29


//APB2 peripheral (RCC_APB2EBR)
#define  RCC_APB2_TIM1LP				BIT_MASK_0
#define  RCC_APB2_TIM8LP				BIT_MASK_1
#define  RCC_APB2_USART1LP				BIT_MASK_4
#define  RCC_APB2_USART6LP				BIT_MASK_5
#define  RCC_APB2_ADC1LP				BIT_MASK_8
#define  RCC_APB2_ADC2LP				BIT_MASK_9
#define  RCC_APB2_ADC3LP				BIT_MASK_10
#define  RCC_APB2_SDIOLP				BIT_MASK_11
#define  RCC_APB2_SPI1LP				BIT_MASK_12
#define  RCC_APB2_SYSCFGLP	   	    	BIT_MASK_14
#define  RCC_APB2_TIM9LP				BIT_MASK_16
#define  RCC_APB2_TIM10LP		  		BIT_MASK_17
#define  RCC_APB2_TIM11LP		    	BIT_MASK_18

/* MCO1 */
#define RCC_MCO1_HSI					( (uint32_t)0x00U)
#define RCC_MCO1_LSE					BIT_MASK_21
#define RCC_MCO1_HSE					BIT_MASK_22
#define RCC_MCO1_PLL					( BIT_MASK_21 | BIT_MASK_22 )
#define RCC_MCO1_PRE_OFF				( (uint32_t) 0x00U)
#define RCC_MCO1_PRE_2					BIT_MASK_26
#define RCC_MCO1_PRE_3					( BIT_MASK_24 | BIT_MASK_26 )
#define RCC_MCO1_PRE_4					( BIT_MASK_25 | BIT_MASK_26 )
#define RCC_MCO1_PRE_5					( BIT_MASK_24 | BIT_MASK_25| BIT_MASK_26 )

/*  MCO2  */
#define RCC_MCO2_SYSCLK					( (uint32_t)0x00U)
#define RCC_MCO2_PLLI2S					BIT_MASK_30
#define RCC_MCO2_HSE					BIT_MASK_31
#define RCC_MCO2_PLL					( BIT_MASK_30 | BIT_MASK_31 )
#define RCC_MCO2_PRE_OFF				( (uint32_t) 0x00U)
#define RCC_MCO2_PRE_2					BIT_MASK_29
#define RCC_MCO2_PRE_3					( BIT_MASK_27 | BIT_MASK_29 )
#define RCC_MCO2_PRE_4					( BIT_MASK_28 | BIT_MASK_29 )
#define RCC_MCO2_PRE_5					( BIT_MASK_27 | BIT_MASK_28| BIT_MASK_29 )



/* PERIFRALS  PRESCALERS  */

// HPRE
#define RCC_HPRE_OFF 					( 0x00 )
#define RCC_HPRE_2						(  BIT_MASK_7)
#define RCC_HPRE_4						(  BIT_MASK_7 | BIT_MASK_4 )
#define RCC_HPRE_8						(  BIT_MASK_7 | BIT_MASK_5 )
#define RCC_HPRE_16						(  BIT_MASK_7 | BIT_MASK_5 | BIT_MASK_4 )
#define RCC_HPRE_64						(  BIT_MASK_7 | BIT_MASK_6 )
#define RCC_HPRE_128					(  BIT_MASK_7 | BIT_MASK_6 | BIT_MASK_4 )
#define RCC_HPRE_256					(  BIT_MASK_7 | BIT_MASK_6 | BIT_MASK_5 )
#define RCC_HPRE_512					(  BIT_MASK_7 | BIT_MASK_6 | BIT_MASK_5  | BIT_MASK_4 )

// PPRE1
#define RCC_PPRE1_1						( (uint32_t) 0x00U )
#define RCC_PPRE1_2						( BIT_MASK_12 )
#define RCC_PPRE1_4						( BIT_MASK_12 |  BIT_MASK_10 )
#define RCC_PPRE1_8						( BIT_MASK_12 |  BIT_MASK_11 )
#define RCC_PPRE1_16					( BIT_MASK_12 |  BIT_MASK_11 | BIT_MASK_10 )

// PPRE2
#define RCC_PPRE2_1						( (uint32_t) 0x00U )
#define RCC_PPRE2_2						( BIT_MASK_15 )
#define RCC_PPRE2_4						( BIT_MASK_15 |  BIT_MASK_13 )
#define RCC_PPRE2_8						( BIT_MASK_15 |  BIT_MASK_14 )
#define RCC_PPRE2_16					( BIT_MASK_15 |  BIT_MASK_14 | BIT_MASK_13 )








/**
 * Turn the Selected clock ON
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_enableClock (uint32_t RCC_clock );

/**
 * Turn the Selected clock OFF
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 * CAUTION : Clock will not be disabled if the clock is selected as system clock.
 */
uint32_t RCC_disableClock(uint32_t RCC_clock );


/**
 * Select the system clock between ( RCC_SYS_CLOCK_HSI, RCC_SYS_CLOCK_HSE, RCC_SYS_CLOCK_PLL ).
 * Make that the clock are enabled before selecting it.
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_selectSysClock(uint32_t RCC_sysClock);

/**
 * Configure PLL prescalers and the choosing the source clock of it.
 * This function takes point of structure that holds all the configurations.
 *
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 *
 * CAUTION : PLL should be disabled before configuring it.
 */
uint32_t RCC_cfgPll(RCC_cfg_pll_t * RCC_cfg_pll);


/**
 * This function gives the frequency of the current system clock in the sent pointer.
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_getSysClockFrequency(uint32_t* returnFreq);


/**
 *  This function set the peripherals in this Bus ( ON/OFF )
 *  By getting the peripheral name and it's status
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_AHB1_status(uint32_t RCC_AHB1, uint32_t RCC_periState);

/**
 *  This function set the peripherals in this Bus ( ON/OFF )
 *  By getting the peripheral name and it's status
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_AHB2_status(uint32_t RCC_AHB2, uint32_t RCC_periState);

/**
 *  This function set the peripherals in this Bus ( ON/OFF )
 *  By getting the peripheral name and it's status
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_APB1_status(uint32_t RCC_APB1, uint32_t RCC_periState);

/**
 *  This function set the peripherals in this Bus ( ON/OFF )
 *  By getting the peripheral name and it's status
 * Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_APB2_status(uint32_t RCC_APB2, uint32_t RCC_periState);


/**
 *  Select the which clock will be the output of MCO1 pin and then choose the prescaler of it.
 * 	Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 *	NOTE : Set and cleared by software. Clock source selection may generate glitches on MCO1.
 * 	It is highly recommended to configure these bits only after reset before enabling the external
 * 	oscillators and the PLLs.
 */
uint32_t RCC_setMCO1_Clock(uint32_t RCC_MCO1_out, uint32_t RCC_MCO1_prescaler);

/**
 *  Select the which clock will be the output of MCO1 pin and then choose the prescaler of it.
 * 	Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 * NOTE : Set and cleared by software. Clock source selection may generate glitches on MCO2.
 * It is highly recommended to configure these bits only after reset before enabling the external
 * oscillators and the PLLs.
 */
uint32_t RCC_setMCO2_Clock(uint32_t RCC_MCO2_out, uint32_t RCC_MCO2_prescaler);


/**
 *  Set the presecaler of the bus
 * 	Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_setHPRE(uint32_t RCC_HPRE);


uint32_t RCC_getHPRE(uint32_t * prescaler);
/**
 *  Set the presecaler of the bus
 * 	Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_setHPRE1(uint32_t RCC_PPRE1);

/**
 *  Set the presecaler of the bus
 * 	Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_setHPRE2(uint32_t RCC_PPRE2);


/**
 *  Set the presecaler of the bus
 * 	Return => 0 : if the function success
 * 		  => otherwise : Error occurred and should return to error table
 */
uint32_t RCC_setRTCPRE(uint32_t RCC_RTCPRE);


/**
 * 	Set the clock of the system
 * 	NOTE : The system clock will be PLL and configured as the wanted clock
 * 	CAUTION : The valied range of the clock from 50 to 168.
 */
uint32_t RCC_setSysClock(uint32_t RCC_Clock);

 #endif /* RCC_H_ */
