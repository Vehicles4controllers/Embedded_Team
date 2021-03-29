/***************************************************************************************************************************************************/
/*                                                              SysTick Timer Driver                                                               */
/* File Name : STK_config.h 																	    											   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 21 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef STK_CONFIG_H
#define STK_CONFIG_H

/***************************************************************************************************************************************************/ 
/*                                                                 Configuration															       */
/* STK Registers : Section 3.3 Page 137 					         																			   */
/***************************************************************************************************************************************************/
/* MSTK_CLKSOURCE: 	MSTK_SYS_CLK_DIV_4
					MSTK_SYS_CLK	   */
#define MSTK_CLKSOURCE		MSTK_SYS_CLK_DIV_4

/* MSTK_STATE: 	MSTK_DISABLE
				MSTK_ENABLE  */
#define MSTK_STATE			MSTK_DISABLE

/* MSTK_INTERRUPT: 	MSTK_DISABLE
					MSTK_ENABLE  */
#define MSTK_INTERRUPT		MSTK_DISABLE

/* AHP Clock */
#define MSTK_SYS_CLK_CLK	12000000
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/ 
/*                                                                      Info                                                                       */
/***************************************************************************************************************************************************/
/*                                                            Interval Modes Functions                                                             */
/* MSTK_voidSetIntervalSingle  : At under-flow -> Disable STK Interrupt - Stop Timer - Load Zero to STK_LOAD                                       */
/* MSTK_voidSetIntervalPeriodic: At under-flow ->           xx          -     xx     -         xx                                                  */
/* MSTK_voidSetIntervalSpecial : At under-flow -> Disable STK Interrupt -     xx     - Load Zero to STK_LOAD                                       */
/* MSTK_voidStart              : Doesn't use interrupt and Loads Maximum Value to STK_LOAD (0xFFFFFF)                                              */
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/ 