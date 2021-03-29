/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_program.c 																	    											   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 18 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                             Header Files Inclusions 															   */
/***************************************************************************************************************************************************/ 
/* Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GPIO_int.h"	// GPIO

/* Own Driver Files */
#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                 Global Variables                                                                */
/***************************************************************************************************************************************************/
extern const MUART_config_Type MUART_Config[MUART_MAX_CH];
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                                    Functions                                                                    */
/***************************************************************************************************************************************************/
/* Initialization */
void MUART_voidInit(void)
{
	MUART_CH_Type Local_Counter = UART0;
	for (Local_Counter=UART0; Local_Counter<MAX_UARTS; Local_Counter++)
	{
		if      (MUART_Config[Local_Counter].UART_State == ENABLE)
		{
		    /* Clear Control Registers */
//			MUART[Local_Counter]->LCRH = MUART_0;
//			MUART[Local_Counter]->CTL  = MUART_0;
			/* Connect Clock */
			SET_BIT(RCGCUART,Local_Counter);
			/* Configure Baud Rate */
			MUART_voidSetBaudRate(Local_Counter,MUART_Config[Local_Counter].u32BaudRate);
			/* Configure Word Length */
			GIV_BIT(MUART[Local_Counter]->LCRH,MUART_Config[Local_Counter].WordLength,WLEN0_BIT);
			/* Configure Parity */
			GIV_BIT(MUART[Local_Counter]->LCRH,MUART_Config[Local_Counter].ParityMode,MUART_0);
			/* Configure Stop Bits */
			GIV_BIT(MUART[Local_Counter]->LCRH,MUART_Config[Local_Counter].StopBits,STP2_BIT);
			/* Enable FIFO */
			SET_BIT(MUART[Local_Counter]->LCRH,FEN_BIT);
			/* GPIO */
			GPIO_voidConnectClock(PINS[Local_Counter].PORT1);
			GPIO_voidConnectClock(PINS[Local_Counter].PORT2);
			GPIO_voidSetBus(PINS[Local_Counter].PORT1,AHB);
			GPIO_voidEnableDigitalFunction(PINS[Local_Counter].PORT1,PINS[Local_Counter].pin1);
			GPIO_voidEnableAlternateFunction(PINS[Local_Counter].PORT1,PINS[Local_Counter].pin1);
			GPIO_voidSetBus(PINS[Local_Counter].PORT2,AHB);
			GPIO_voidEnableDigitalFunction(PINS[Local_Counter].PORT2,PINS[Local_Counter].pin2);
			GPIO_voidEnableAlternateFunction(PINS[Local_Counter].PORT2,PINS[Local_Counter].pin2);
			GPIO_voidPinMUltiplexerSet(PINS[Local_Counter].PORT1,PINS[Local_Counter].pin1,1);
			GPIO_voidPinMUltiplexerSet(PINS[Local_Counter].PORT2,PINS[Local_Counter].pin2,1);
			/* Configure RT State */
			switch (MUART_Config[Local_Counter].RTControl)
			{
				case ENABLE_RECEIVER   :
					SET_BIT(MUART[Local_Counter]->CTL,RXE_BIT);
					//CLR_BIT(MUART[Local_Counter]->CTL,TXE_BIT);
					break;
				case ENABLE_TRANSMITTER:
					//CLR_BIT(MUART[Local_Counter]->CTL,RXE_BIT);
					SET_BIT(MUART[Local_Counter]->CTL,TXE_BIT);
					break;
				case ENABLE_BOTH       :
					SET_BIT(MUART[Local_Counter]->CTL,RXE_BIT);
					SET_BIT(MUART[Local_Counter]->CTL,TXE_BIT);
				default                : 
					/* Do Nothing */ 							
					break;
			}
			/* Enable Module */
			SET_BIT(MUART[Local_Counter]->CTL,UARTEN_BIT);
			/* Initialize Status Register */
			MUART[Local_Counter]->FR = MUART_0;
		}
		else if (MUART_Config[Local_Counter].UART_State == DISABLE)
		{
			/* Clear Control Registers */
//			MUART[Local_Counter]->LCRH = MUART_0;
//			MUART[Local_Counter]->CTL  = MUART_0;
		}
		else 
		{
			/* Do Nothing */
		}
	}
}

/* Set BaudRate */
void MUART_voidSetBaudRate(MUART_CH_Type Copy_UARTChannel,u32 Copy_u32BaudRate)
{
    f64 Local_f64BRD              = (MUART_SYS_CLK / MUART_CLK_DIVIDER) / Copy_u32BaudRate;
    f64 Local_f64Fractional       = ((Local_f64BRD - (u16)Local_f64BRD) * MUART_64) + MUART_HALF;
	MUART[Copy_UARTChannel]->IBRD = (u16)Local_f64BRD;
	MUART[Copy_UARTChannel]->FBRD = (u8)Local_f64Fractional;
}

/* Set Loop Back Mode */
void MUART_voidSetLoopBackMode(MUART_CH_Type Copy_UARTChannel)
{
	SET_BIT(MUART[Copy_UARTChannel]->CTL,LBE_BIT);
}

/* Send Data Synchronous */
void MUART_voidSendDataSynch(MUART_CH_Type Copy_UARTChannel, pu8 Copy_pu8Data)
{
	if (Copy_UARTChannel < MAX_UARTS)
	{	
		while (*Copy_pu8Data)
		{
			MUART[Copy_UARTChannel]->DR = *Copy_pu8Data;
			while(GET_BIT(MUART[Copy_UARTChannel]->FR,TXFF_BIT));
			Copy_pu8Data++;
		}
	}
	else
	{
		/* Do Nothing */
	}
}

void MUART_voidWriteNum16Bit(s16 Copy_u16Num)
{
    u8  Local_u8DigitNum = 0;
    u16 Local_u16Num     = Copy_u16Num;
    u8  Local_u8Counter  = 0;
    u8 y =0;
    u8 Local_arru8Num[50];
    if (Copy_u16Num < 0)
    {
        Copy_u16Num *= -1;
        Local_u16Num *= -1;
        MUART_voidSendDataSynch(UART0, "-");
    }
    if (!Copy_u16Num)
    {
        Local_u8DigitNum = 1;
    }
    else
    {
        while (Local_u16Num)
        {
            Local_u16Num /= 10;
            ++Local_u8DigitNum;
        }
    }

    for (Local_u8Counter=Local_u8DigitNum; Local_u8Counter>0; Local_u8Counter--)
    {
        Local_u16Num = Copy_u16Num%10;
        Local_arru8Num[Local_u8Counter-1] = Local_u16Num;
        Copy_u16Num = Copy_u16Num/10;
    }

    for (Local_u8Counter=0; Local_u8Counter<Local_u8DigitNum; Local_u8Counter++)
    {

        y = Local_arru8Num[Local_u8Counter]+'0';
        MUART_voidSendDataSynch(UART0, &(y));
    }
}

/* Receive Data Synchronous with Data Length */
void MUART_voidReceiveDataSynch(MUART_CH_Type Copy_UARTChannel, pu8 Copy_pu8Data, u8 Copy_u8DataLength)
{
	if (Copy_UARTChannel < MAX_UARTS)
	{	
		while (Copy_u8DataLength--)
		{
			while(GET_BIT(MUART[Copy_UARTChannel]->FR,RXFE_BIT));
			*Copy_pu8Data = MUART[Copy_UARTChannel]->DR;
			Copy_pu8Data++;
		}
	}
	else
	{
		/* Do Nothing */
	}
}
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
