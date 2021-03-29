/***************************************************************************************************************************************************/
/*                                                              SysTick Timer Driver                                                               */
/* File Name : STK_private.h 																	    											   */
/* Auhor     : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 21 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/***************************************************************************************************************************************************/ 
/*                                                              Registers Definitions 															   */
/* Address		   : 0xE000E010-0xE000E01F																					   					   */
/* Core peripheral : System timer																							   					   */
/* Register map    : Table 3-8 on page 134 																					   					   */  
/***************************************************************************************************************************************************/ 
/* STK Base Address */
#define MSTK_BASE_ADDRESS		0xE000E010

/* STK Register */
typedef struct
{
	volatile u32 CTRL   ;			// SysTick Control and Status Register (STCTRL)
	volatile u32 RELOAD ;			// SysTick Reload Value Register (STRELOAD)
	volatile u32 CURRENT;			// SysTick Current Value Register (STCURRENT)
}MSTK_Type;

#define MSTK					((volatile MSTK_Type*)MSTK_BASE_ADDRESS)
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/ 
/*                                                                 Registers Bits 			     												   */
/* STK Registers : Section 3.3 Page 137 					         																			   */
/***************************************************************************************************************************************************/ 
/* SysTick control and status register (STK_CTRL) */
#define COUNT_BIT				16	// Returns 1 if timer counted to 0 since last time this was read
#define CLK_SRC_BIT				2	// Clock source selection 
#define INTEN_BIT				1	// Interrupt Enable
#define ENABLE_BIT				0	// Counter enable 
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/  
/*                                                                     Private															       	   */
/***************************************************************************************************************************************************/ 
/* Magic Numbers */
#define MSTK_INITIAL_VALUE 		0
#define MSTK_0     				0
#define MSTK_4     				4 
#define MSTK_8     				8 
#define MSTK_1000     			1000 
#define MSTK_1000000     		1000000
#define MSTK_0xFFFFFF     		0xFFFFFF

/* States */
#define MSTK_DISABLE			0
#define MSTK_ENABLE 			1

/* Interval Modes */
#define MSTK_SINGLE_INTERVAL	0
#define MSTK_PERIOD_INTERVAL	1
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                 Global Variables                                                                */
/***************************************************************************************************************************************************/
static u8  MSTK_u8IntervalMode;		// Define Variable for interval mode
static u32 MSTK_u32Clk;
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                CallBack Functions                                                               */
/***************************************************************************************************************************************************/
#define NULL				((void*)0x00)
static void (*MSTK_CallBack)(void) = NULL;

/* ISR */
void SysTick_Handler(void)
{
	u8 Local_u8Temporary = MSTK_INITIAL_VALUE;
	
	if      (MSTK_u8IntervalMode == MSTK_SINGLE_INTERVAL)
	{
		/* Disable STK Interrupt */
		CLR_BIT(MSTK->CTRL,TICKINT_BIT);
		/* Stop Timer */
		CLR_BIT(MSTK->CTRL,ENABLE_BIT);
		/* Load Zero to STK_LOAD */
		MSTK->RELOAD = MSTK_0;
		MSTK->CURRENT  = MSTK_0;
	}
	else
	{
		/* Do Nothing */
	}
	
	/* Callback Notification */
	if (MSTK_CallBack != NULL)
	{
		(*MSTK_CallBack)();
	}
	else
	{
		/* Do Nothing */
	}
	
	/* Clear Interrupt Flag */
	Local_u8Temporary = GET_BIT(MSTK->CTRL,COUNTFLAG_BIT);
}
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/ 