/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_interface.h 																	    										   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 18 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef UART_INRERFACE_H
#define UART_INRERFACE_H

/***************************************************************************************************************************************************/ 
/*                                                                  Macros/Enums																   */
/***************************************************************************************************************************************************/ 
typedef enum
{
	UART0,
	UART1,
	UART2,
	UART3,
	UART4,
	UART5,
	UART6,
	UART7,
	MAX_UARTS
}MUART_CH_Type;
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                              Functions Declaration															   */
/***************************************************************************************************************************************************/
/* Initialization */
void MUART_voidInit(void);

/* Set BaudRate */
void MUART_voidSetBaudRate(MUART_CH_Type Copy_UARTChannel,u32 Copy_u32BaudRate);

/* Set Loop Back Mode */
void MUART_voidSetLoopBackMode(MUART_CH_Type Copy_UARTChannel);

/* Send Data Synchronous */
void MUART_voidSendDataSynch(MUART_CH_Type Copy_UARTChannel, pu8 Copy_pu8Data);
void MUART_voidWriteNum16Bit(s16 Copy_u16Num);

/* Receive Data Synchronous with Data Length */
void MUART_voidReceiveDataSynch(MUART_CH_Type Copy_UARTChannel, pu8 Copy_pu8Data, u8 Copy_u8DataLength);
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/ 
