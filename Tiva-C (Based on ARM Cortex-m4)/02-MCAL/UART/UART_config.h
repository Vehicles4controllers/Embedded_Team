/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_config.h 																	    											   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 18 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef UART_CONFIG_H
#define UART_CONFIG_H

/***************************************************************************************************************************************************/ 
/*                                                                 Configuration															       */
/* UART Registers : Section     																								   */
/***************************************************************************************************************************************************/
/* Number of UART Channels */
#define MUART_MAX_CH	8 

/* System Clock */
#define MUART_SYS_CLK	16000000.0

/* UART State Type */
typedef enum
{
	DISABLE,
	ENABLE
}MUART_State_Type;

/* Data Length Type */
typedef enum
{
	DATA_5BIT,
	DATA_6BIT,
	DATA_7BIT,
	DATA_8BIT
}MUART_WordLength_Type;

/* Parity Type */
typedef enum
{	NO_PARITY   = 0  ,
	EVEN_PARITY = 6  ,
	ODD_PARITY  = 2  ,
	STICK0      = 134,
	STICK1      = 130
}MUART_Parity_Type;

/* RT Control Type */
typedef enum 
{
	ENABLE_RECEIVER   ,
	ENABLE_TRANSMITTER,
	ENABLE_BOTH
}MUART_RTControl_Type;

/* Stop Bits Type */
typedef enum 
{
	STOP_1BIT,
	STOP_2BITS
}MUART_StopBits_Type;

/* Configuration Type */
typedef struct 
{
	MUART_State_Type      UART_State ;
	MUART_State_Type      FIFO_State ;
	MUART_WordLength_Type WordLength ;
	MUART_Parity_Type     ParityMode ;
	MUART_RTControl_Type  RTControl  ;
	MUART_StopBits_Type   StopBits   ;
	u32                   u32BaudRate;
}MUART_config_Type;
/***************************************************************************************************************************************************/ 

#endif
/***************************************************************************************************************************************************/ 
