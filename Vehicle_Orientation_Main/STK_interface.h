/***************************************************************************************************************************************************/
/*                                                              SysTick Timer Driver                                                               */
/* File Name : STK_interface.h 																	    										  	   */
/* Auhor     : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 21 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef STK_INRERFACE_H
#define STK_INRERFACE_H

#include "STD_TYPES.h"
/***************************************************************************************************************************************************/ 
/*                                                                  Macros/Enums																   */
/***************************************************************************************************************************************************/ 
typedef enum
{
	MSTK_SYS_CLK_DIV_4,
	MSTK_SYS_CLK			
}MSTK_CLKSource_Type;

typedef enum 
{
	MSTK_TIME_MS,
	MSTK_TIME_US
}MSTK_TimeUnit_Type;
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                              Functions Declaration															   */
/***************************************************************************************************************************************************/
/* Initialization */
void                MSTK_voidInit                (void);
/* Select Clock Source */
void                MSTK_voidSelectCLKSOurce     (MSTK_CLKSource_Type Copy_u8CLKSOurce);
/* Read Clock Source */
MSTK_CLKSource_Type MSTK_ReadCLKSOurce           (void);
/* Synchronous */
void                MSTK_voidSetBusyWait         (uint32_t Copy_u32Time);
/* Asynchronous */
void                MSTK_voidSetIntervalSingle   (uint32_t Copy_u32Time, void (*Copy_ptr)(void));
void                MSTK_voidSetIntervalPeriodic (uint32_t Copy_u32Time, void (*Copy_ptr)(void));
void                MSTK_voidPauseInterval       (void);
void                MSTK_voidResumeInterval      (void);
void                MSTK_voidStopInterval        (void);
void                MSTK_voidStart               (void);							/* Load Maximum Value */
void                MSTK_voidPause               (void);
void                MSTK_voidResume              (void);
void                MSTK_voidStop                (void);
/* Get Time Value */
uint32_t                 MSTK_u32GetElapsedTime       (MSTK_TimeUnit_Type Copy_Unit);
uint32_t                 MSTK_u32GetRemainingTime     (MSTK_TimeUnit_Type Copy_Unit);
/* Interrupt */
void                MSTK_voidEnableInterrupt	 (void);
void                MSTK_voidDisableInterrupt    (void);
void                MSTK_voidClearInterruptFlag  (void);
u8                  MSTK_u8ReadInterruptFlag     (void);							/* This Function Clears Interrupt Flag */
void                MSTK_voidSetCallBack         (void (*Copy_ptr)(void));
/***************************************************************************************************************************************************/
void MSTK_voidScheduleTasks();
void MSTK_voidCreateTask(u8 Copy_u8TaskID, u16 Copy_u16Period, void (*Copy_voidFPtr)(void));

void MSTK_voidListMyTasks(void);

#endif
/***************************************************************************************************************************************************/ 
