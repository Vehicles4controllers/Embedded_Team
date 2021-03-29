/***************************************************************************************************************************************************/
/*                                                              Wheel Encoder Driver                                                               */
/* File Name : ENCODER_program.c 																    											   */
/* Aurthor   : Embedded Team																 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 21 FEB 2021 																	 	    											   */
/* MC        : Tivaâ„¢ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : HAL				 																	    										   */
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                             Header Files Inclusions 															   */
/***************************************************************************************************************************************************/ 
/* Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include"GPIO_int.h"		// GPIO
#include"Interrupt_int.h"	// INT
#include"UART_interface.h"  //UART

/* Own Driver Files */
#include "ENCODER_interface.h"
#include "ENCODER_config.h"
#include "ENCODER_private.h"
/***************************************************************************************************************************************************/

static u32 Global_u32Counter  = 0;
static u32 Global_u32Distance = 0;
/***************************************************************************************************************************************************/ 
/*                                                                    Functions                                                                    */
/***************************************************************************************************************************************************/
/* Initialization */
void HENCODER_voidInit(void)
{
    Load_Vector_Table();
	/* A Phase Initialization */
    GPIO_voidInitializeDigitalPin(HENCODER_A_PHASE_PORT,HENCODER_A_PHASE_PIN,INPUT_PULLUP,Drive_8mA);
    GPIO_voidSetPULL_UP_DN(HENCODER_A_PHASE_PORT,HENCODER_A_PHASE_PIN,PULLUP);
    GPIO_voidSetInterruptEvent(HENCODER_A_PHASE_PORT,HENCODER_A_PHASE_PIN,FallingEdge);
    Interrupt_voidEnable(HENCODER_INT_ENABLE);
}

/* ISR */
void HENCODER_voidOperationISR(void)
{
	Global_u32Counter++;

    if ((Global_u32Counter%HENCODER_CALIBRATION_VALUE) == 0)
    {
        Global_u32Distance++;
    }
    else
    {
        /* Do Nothing */
    }

    MUART_voidWriteNum16Bit(Global_u32Counter);
    MUART_voidSendDataSynch(UART0, "\n");
}

/* Read the Distance in Meter */
u32 HENCODER_u32ReadDistanceInMeter(void)
{
    return Global_u32Distance;
}

/* Reset */
void HENCODER_voidResetCounter(void)
{
	Global_u32Counter = 0;
}
void HENCODER_voidResetDistance(void)
{
	Global_u32Distance = 0;
}
void HENCODER_voidResetEncoder(void)
{
	Global_u32Counter = 0;
	Global_u32Distance = 0;
}

/* Turn off Encoder */
void HENCODER_voidTurnOffEncoder(void)
{
	Global_u32Counter = 0;
	Global_u32Distance = 0;
	Interrupt_voidDisable(HENCODER_INT_ENABLE);
}
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
