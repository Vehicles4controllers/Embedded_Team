/***************************************************************************************************************************************************/
/*                                                              SysTick Timer Driver                                                               */
/* File Name : STK_program.c 																	    											   */
/* Aurthor   : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 21 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                             Header Files Inclusions 															   */
/***************************************************************************************************************************************************/ 
/* Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* Own Driver Files */
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

#include "GPIO_int.h"

extern void IMU_CalculateAngle(void);
extern void KalmanFilter_voidGetReadings(void);


struct task
{
    void (*taskISR)(void);
    uint32_t periodicity;
};

struct task MyTasks[MUART_NUMBER_OF_TASKS];

/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                                    Functions                                                                    */
/***************************************************************************************************************************************************/
/* Initialization */
void MSTK_voidInit(void)
{
	/* Apply Clock Source */ 
	#if   MSTK_CLKSOURCE == MSTK_SYS_CLK_DIV_4
	SET_BIT(MSTK->CTRL,CLK_SRC_BIT);
		MSTK_u32Clk = MSTK_10000 / (MSTK_SYS_CLK_CLK / ( MSTK_1000000));
	#elif MSTK_CLKSOURCE == MSTK_SYS_CLK
		SET_BIT(MSTK->CTRL,CLK_SRC_BIT);
		MSTK_u32Clk = MSTK_10000 / (MSTK_SYS_CLK_CLK / MSTK_1000000);
	#else
		#error("Configuration Error :: Wrong MSTK_CLKSOURCE")
	#endif
	
	/* SysTick State */ 
	#if   MSTK_STATE == MSTK_DISABLE
		CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	#elif MSTK_STATE == MSTK_ENABLE
		SET_BIT(MSTK->CTRL,ENABLE_BIT);
	#else
		#error("Configuration Error :: Wrong MSTK_STATE")
	#endif
	
	/* SysTick Interrupt State */  
	#if   MSTK_INTERRUPT == MSTK_DISABLE
		CLR_BIT(MSTK->CTRL,INTEN_BIT);
	#elif MSTK_INTERRUPT == MSTK_ENABLE
		SET_BIT(MSTK->CTRL,INTEN_BIT);
	#else
		#error("Configuration Error :: Wrong MSTK_INTERRUPT")
	#endif
}

/* Select Clock Source */
void MSTK_voidSelectCLKSOurce(MSTK_CLKSource_Type Copy_CLKSource)
{
	switch (Copy_CLKSource)
	{
		case MSTK_SYS_CLK_DIV_4:
			CLR_BIT(MSTK->CTRL,CLK_SRC_BIT);
			MSTK_u32Clk = MSTK_SYS_CLK_CLK / MSTK_4;
			break;		 
		case MSTK_SYS_CLK      : 
			SET_BIT(MSTK->CTRL,CLK_SRC_BIT); 
			MSTK_u32Clk = MSTK_SYS_CLK_CLK;
			break;	 	 
		default                : 
			/* Do Nothing */	
			break;
	}
}

/* Read Clock Source */
MSTK_CLKSource_Type MSTK_ReadCLKSOurce(void)
{
	MSTK_CLKSource_Type Local_CLKSource = GET_BIT(MSTK->CTRL,CLK_SRC_BIT);
	return Local_CLKSource;
}

/* Synchronous */
void MSTK_voidSetBusyWait(uint32_t Copy_u32Time)
{
	uint32_t Local_u32Load = MSTK_INITIAL_VALUE;
	/* Restart Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	MSTK->CURRENT = MSTK_0;
	/* Calculation and Load Ticks to STK_LOAD register */
	Local_u32Load = (Copy_u32Time)-1;// - (MSTK_u32Clk/MSTK_10000);
	MSTK->RELOAD  = Local_u32Load;
	/* Start Timer */
	SET_BIT(MSTK->CTRL,ENABLE_BIT);
	/* Wait till flag is raised when timer counted to 0 */
	while(!(GET_BIT(MSTK->CTRL,COUNT_BIT)));
	/* Stop Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	/* Load Zero to STK_LOAD */
	MSTK->RELOAD  = MSTK_0;
	MSTK->CURRENT = MSTK_0;	
}
	
/* Asynchronous */
void MSTK_voidSetIntervalSingle(uint32_t Copy_u32Time, void (*Copy_ptr)(void))
{
	uint32_t Local_u32Load = MSTK_INITIAL_VALUE;
	/* Restart Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	MSTK->CURRENT  = MSTK_0;
	/* Calculation and Load Ticks to STK_LOAD register */
	/* Calculation and Load Ticks to STK_LOAD register */
	Local_u32Load = (Copy_u32Time/MSTK_10000) - (MSTK_u32Clk);
	MSTK->RELOAD  = Local_u32Load;
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	/* Start Timer */
	SET_BIT(MSTK->CTRL,ENABLE_BIT);
	/* Set Mode to Single */
	MSTK_u8IntervalMode = MSTK_SINGLE_INTERVAL;
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL,INTEN_BIT);
}

void MSTK_voidSetIntervalPeriodic(uint32_t Copy_u32Time, void (*Copy_ptr)(void))
{
    uint32_t Local_u32Load = MSTK_INITIAL_VALUE;
	/* Restart Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	MSTK->CURRENT  = MSTK_0;
	/* Calculation and Load Ticks to STK_LOAD register */
	/* Calculation and Load Ticks to STK_LOAD register */
	Local_u32Load = (Copy_u32Time/MSTK_10000) - (MSTK_u32Clk);
	MSTK->RELOAD  = Local_u32Load;
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	/* Start Timer */
	SET_BIT(MSTK->CTRL,ENABLE_BIT);
	/* Set Mode to Single */
	MSTK_u8IntervalMode = MSTK_PERIOD_INTERVAL;
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL,INTEN_BIT);
}

void MSTK_voidPauseInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(MSTK->CTRL,INTEN_BIT);
	/* Stop Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
}

void MSTK_voidResumeInterval(void)
{
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL,INTEN_BIT);
	/* Start Timer */
	SET_BIT(MSTK->CTRL,ENABLE_BIT);	
}

void MSTK_voidStopInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(MSTK->CTRL,INTEN_BIT);
	/* Stop Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	/* Load Zero to STK_LOAD */
	MSTK->RELOAD = MSTK_0;
	MSTK->CURRENT  = MSTK_0;
}

void MSTK_voidStart(void)
{
	/* Load Maximum Value to STK_LOAD */
	MSTK->RELOAD = MSTK_0xFFFFFF;
	/* Start Timer */
	SET_BIT(MSTK->CTRL,ENABLE_BIT);
}

void MSTK_voidPause(void)
{
	/* Stop Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
}

void MSTK_voidResume(void)
{
	/* Start Timer */
	SET_BIT(MSTK->CTRL,ENABLE_BIT);	
}

void MSTK_voidStop(void)
{
	/* Stop Timer */
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
	/* Load Zero to STK_LOAD */
	MSTK->RELOAD = MSTK_0;
	MSTK->CURRENT  = MSTK_0;
}

/* Get Time Value */
uint32_t  MSTK_u32GetElapsedTime(MSTK_TimeUnit_Type Copy_Unit)
{
    uint32_t Local_u32TicksValue  = MSTK->RELOAD - MSTK->CURRENT;
	uint32_t Local_u32ElapsedTime = MSTK_INITIAL_VALUE;
	switch (Copy_Unit)
	{
		case MSTK_TIME_MS: Local_u32ElapsedTime = Local_u32TicksValue/(MSTK_u32Clk/MSTK_1000);		break;
		case MSTK_TIME_US: Local_u32ElapsedTime = Local_u32TicksValue/(MSTK_u32Clk/MSTK_1000000);	break;  
		default          : /* Do Nothing */															break;
	}
	return Local_u32ElapsedTime;
}

uint32_t  MSTK_u32GetRemainingTime(MSTK_TimeUnit_Type Copy_Unit)
{
    uint32_t Local_u32TicksValue    = MSTK->CURRENT;
    uint32_t Local_u32RemainingTime = MSTK_INITIAL_VALUE;
	switch (Copy_Unit)
	{
		case MSTK_TIME_MS: Local_u32RemainingTime = Local_u32TicksValue/(MSTK_u32Clk/MSTK_1000);		break;
		case MSTK_TIME_US: Local_u32RemainingTime = Local_u32TicksValue/(MSTK_u32Clk/MSTK_1000000);	break;
		default          : /* Do Nothing */															break;
	}
	return Local_u32RemainingTime;
}

/* Interrupt */
void MSTK_voidEnableInterrupt(void)
{
	SET_BIT(MSTK->CTRL,ENABLE_BIT);
}
void MSTK_voidDisableInterrupt(void)
{
	CLR_BIT(MSTK->CTRL,ENABLE_BIT);
}
void MSTK_voidClearInterruptFlag(void)
{
	u8 Local_u8InterruptFlag = GET_BIT(MSTK->CTRL,COUNT_BIT);
}
u8   MSTK_u8ReadInterruptFlag(void)							/* This Function Clears Interrupt Flag */
{
	u8 Local_u8InterruptFlag = GET_BIT(MSTK->CTRL,COUNT_BIT); 
	return Local_u8InterruptFlag;
}
void MSTK_voidSetCallBack(void (*Copy_ptr)(void))
{
	MSTK_CallBack = Copy_ptr;
}

void MSTK_voidStartScheduler()
{
    MSTK_voidInit();
    uint32_t Local_u32Load = MSTK_INITIAL_VALUE;
    /* Restart Timer */
    CLR_BIT(MSTK->CTRL,ENABLE_BIT);
    MSTK->CURRENT  = MSTK_0;
    /* Calculation and Load Ticks to STK_LOAD register */
    /* Calculation and Load Ticks to STK_LOAD register */
    Local_u32Load = 80000;
    MSTK->RELOAD  = Local_u32Load;
    /* Save CallBack */
    MSTK_CallBack = MSTK_voidScheduleTasks;
    /* Start Timer */
    SET_BIT(MSTK->CTRL,ENABLE_BIT);
    /* Set Mode to Single */
    MSTK_u8IntervalMode = MSTK_PERIOD_INTERVAL;
    /* Enable STK Interrupt */
    SET_BIT(MSTK->CTRL,INTEN_BIT);

}
void MSTK_voidScheduleTasks()
{
    static uint32_t counter = 0;
    u8 i;
    for(i = 0 ; i < 10 ; i++)
    {
        if((!(counter % MyTasks[i].periodicity)) && (counter > 0))
        {
            (*MyTasks[i].taskISR)();
        }
    }
    counter++;
}

void MSTK_voidCreateTask(u8 Copy_u8TaskID, u16 Copy_u16Period, void (*Copy_voidFPtr)(void))
{
    MyTasks[Copy_u8TaskID].periodicity =Copy_u16Period;
    MyTasks[Copy_u8TaskID].taskISR     =Copy_voidFPtr;
}

void MSTK_voidListMyTasks(void)
{

}

/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
