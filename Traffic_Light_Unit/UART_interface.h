/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_interface.h 																	    										   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																			 	    										   */
/* Date      : 14 AUG 2020 																	 	    											   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef UART_INRERFACE_H
#define UART_INRERFACE_H

/***************************************************************************************************************************************************/ 
/*                                                                  Macros/Enums																   */
/***************************************************************************************************************************************************/
typedef enum 
{
	RXComplete			,
	TXComplete			,
	DataRegisterEmpty
}MUART_Interrupts_Type;
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                              Functions Declaration															   */
/***************************************************************************************************************************************************/
/* Initialization */
void MUART_voidInit(void);

/* Clear Data Register */
void MUART_voidClearDataRegister(void);

/* Enable Interrupt */
void MUART_voidEnableInterrupt(MUART_Interrupts_Type Copy_Interrupt);
/* Disable Interrupt */
void MUART_voidDisableInterrupt(MUART_Interrupts_Type Copy_Interrupt);

/* Read Flags */
u8   MUART_u8GetRXCompleteFlag(void);
u8   MUART_u8GetTXCompleteFlag(void);
u8   MUART_u8GetDataRegisterEmptyFlag(void);
u8   MUART_u8GetFrameErrorFlag(void);
u8   MUART_u8GetDataOverRunFlag(void);
u8   MUART_u8GetParityErrorFlag(void);

/* Clear TXComplete Flag */
void MUART_voidClearTXCompleteFlag(void);

/* Double the USART Transmission Speed | Asynchronous Mode */
void MUART_voidEnableDoubleSpeed(void);
void MUART_voidDisableDoubleSpeed(void);

/* Multi-processor Communication Mode */
void MUART_voidEnableMultiProcessor(void);
void MUART_voidDisableMultiProcessor(void);

/* Send Data Synchronous */
void MUART_voidSendDataSynch(pu8 Copy_pu8Data);

/* Receive Data Synchronous */
void MUART_voidReceiveDataSynch(pu8 Copy_pu8Data, u32 Copy_u32TimeOut);

/* Receive Data Synchronous with Data Length */
void MUART_voidReceiveDataSynchWithDataLength(pu8 Copy_pu8Data, u8 Copy_u8DataLength);

/* Receive Data Synchronous Conditional */
u8   MUART_u8ReceiveDataConditional(pu8 Copy_pu8Data);
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/
