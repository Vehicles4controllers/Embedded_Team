/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_program.c 																	    											   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																			 	    										   */
/* Date      : 14 AUG 2020 																	 	    											   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                             Header Files Inclusions 															   */
/***************************************************************************************************************************************************/ 
/* Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"	// DIO

/* Own Driver Files */
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/
/*                                                                   Functions																	   */
/***************************************************************************************************************************************************/
/* Initialization */
void MUART_voidInit(void)
{
	if      (MUART_STATE == MUART_ENABLE)
	{
		/* Clear Control Registers */
		UCSRA_REGISTER = MUART_0;
		UCSRB_REGISTER = MUART_0;
		UCSRC_REGISTER = MUART_0X80;
		/* Configure Parity */
		#if   ((MUART_PARITY != MUART_NO_PARITY) && (MUART_PARITY != MUART_EVEN_PARITY) && (MUART_PARITY != MUART_ODD_PARITY))
			#error("Configuration Error :: Wrong MUART_PARITY")	
		#endif
		/* Configure Stop BITs */
		#if   ((MUART_STOP_BITS != MUART_STOP_1BIT) && (MUART_STOP_BITS != MUART_STOP_2BITS))		
			#error("Configuration Error :: Wrong MUART_STOP_BITS")
		#endif
		/* Configure UART Mode */
		#if   ((MUART_MODE != MUART_ASYNCHRONOUS) && (MUART_MODE != MUART_SYNCHRONOUS))	
			#error("Configuration Error :: Wrong MUART_MODE")
		#endif
		/* Configure Clock Polarity */
		#if   ((MUART_CLK_POLARITY != MUART_RISING_TX) && (MUART_CLK_POLARITY != MUART_RISING_RX))				
			#error("Configuration Error :: Wrong MUART_CLK_POLARITY")
		#endif
		/* Configure Word Length */
		#if   ((MUART_WORD_LENGTH ==  MUART_DATA_5BIT) || (MUART_WORD_LENGTH ==  MUART_DATA_6BIT) || \
			   (MUART_WORD_LENGTH ==  MUART_DATA_7BIT) || (MUART_WORD_LENGTH ==  MUART_DATA_8BIT))
			//CLR_BIT(UCSRB_REGISTER,UCSZ2_BIT);
			EQU_BIT(UCSRC_REGISTER,MUART_WORD_LENGTH | MUART_PARITY | MUART_STOP_BITS | MUART_MODE | MUART_CLK_POLARITY);
		#elif (MUART_WORD_LENGTH == MUART_DATA_9BIT)
			SET_BIT(UCSRB_REGISTER,UCSZ2_BIT);
			EQU_BIT(UCSRC_REGISTER,(MUART_WORD_LENGTH-MUART_1));
		#else
			#error("Configuration Error :: Wrong MUART_WORD_LENGTH")
		#endif
		/* Configure RT State */
		#if   (MUART_RT_CONTROL == MUART_ENABLE_RECEIVER)
			SET_BIT(UCSRB_REGISTER,RXEN_BIT);
			//CLR_BIT(UCSRB_REGISTER,TXEN_BIT);
		#elif (MUART_RT_CONTROL == MUART_ENABLE_TRANSMITTER)
			//CLR_BIT(UCSRB_REGISTER,RXEN_BIT);
			SET_BIT(UCSRB_REGISTER,TXEN_BIT);
		#elif (MUART_RT_CONTROL == MUART_ENABLE_BOTH)
			SET_BIT(UCSRB_REGISTER,RXEN_BIT);
			SET_BIT(UCSRB_REGISTER,TXEN_BIT);
		#else
			#error("Configuration Error :: Wrong MUART_RT_CONTROL")
		#endif
		/* Configure Baud Rate */
		if (MUART_UBRR < MUART_UBRRL_Full)
		{
			UBRRL_REGISTER = MUART_UBRR;
		}
		else
		{
//			CLR_BIT(UBRRL_REGISTER,URSEL_BIT);
//			MUART_UBRR = ((UBRRH_REGISTER << MUART_8) | UBRRL_REGISTER);
		}
		/* Clear Data Register */
		MUART_voidClearDataRegister();
		/* Configure DIO */
		MDIO_voidSetPinDirection(MUART_PORT,MUART_RXD,INPUT );
		MDIO_voidSetPinDirection(MUART_PORT,MUART_TXD,OUTPUT);
	}
	else if (MUART_STATE == MUART_DISABLE)
	{
		/* Clear Control Registers */
		UCSRA_REGISTER = MUART_0;
		UCSRB_REGISTER = MUART_0;
		UCSRC_REGISTER = MUART_0X80;
	}
	else 
	{
		/* Do Nothing */
	}
	/* return MUART_DONE; */
}

/* Clear Data Register */
void MUART_voidClearDataRegister(void)
{
	UDR_REGISTER = MUART_0;
	/* return MUART_DONE; */
}

/* Enable Interrupt */
void MUART_voidEnableInterrupt(MUART_Interrupts_Type Copy_Interrupt)
{
	switch(Copy_Interrupt)
	{
		case RXComplete       : SET_BIT(UCSRB_REGISTER,RXCIE_BIT); /* return MUART_DONE; */	break;
		case TXComplete       : SET_BIT(UCSRB_REGISTER,TXCIE_BIT); /* return MUART_DONE; */	break;
		case DataRegisterEmpty: SET_BIT(UCSRB_REGISTER,UDRIE_BIT); /* return MUART_DONE; */	break;
		default               : /* return MUART_WRONG_INT; */								break;
	}
}

/* Disable Interrupt */
void MUART_voidDisableInterrupt(MUART_Interrupts_Type Copy_Interrupt)
{
	switch(Copy_Interrupt)
	{
		case RXComplete       : CLR_BIT(UCSRB_REGISTER,RXCIE_BIT); /* return MUART_DONE; */	break;
		case TXComplete       : CLR_BIT(UCSRB_REGISTER,TXCIE_BIT); /* return MUART_DONE; */	break;
		case DataRegisterEmpty: CLR_BIT(UCSRB_REGISTER,UDRIE_BIT); /* return MUART_DONE; */	break;
		default               : /* return MUART_WRONG_INT; */								break;
	}
}

/* Read Flags */
u8   MUART_u8GetRXCompleteFlag(void)
{
	return(GET_BIT(UCSRA_REGISTER,RXC_BIT));
	/* return MUART_DONE; */
}
u8   MUART_u8GetTXCompleteFlag(void)
{
	return(GET_BIT(UCSRA_REGISTER,TXC_BIT));
	/* return MUART_DONE; */
}
u8   MUART_u8GetDataRegisterEmptyFlag(void)
{
	return(GET_BIT(UCSRA_REGISTER,UDRE_BIT));
	/* return MUART_DONE; */
}
u8   MUART_u8GetFrameErrorFlag(void)
{
	return(GET_BIT(UCSRA_REGISTER,FE_BIT));
	/* return MUART_DONE; */
}
u8   MUART_u8GetDataOverRunFlag(void)
{
	return(GET_BIT(UCSRA_REGISTER,DOR_BIT));
	/* return MUART_DONE; */
}
u8   MUART_u8GetParityErrorFlag(void)
{
	return(GET_BIT(UCSRA_REGISTER,PE_BIT));
	/* return MUART_DONE; */
}

/* Clear TXComplete Flag */
void MUART_voidClearTXCompleteFlag(void)
{
	SET_BIT(UCSRA_REGISTER,TXC_BIT);
	/* return MUART_DONE; */
}

/* Double the USART Transmission Speed | Asynchronous Mode */
void MUART_voidEnableDoubleSpeed(void)
{
	SET_BIT(UCSRA_REGISTER,U2X_BIT);
	/* return MUART_DONE; */
}
void MUART_voidDisableDoubleSpeed(void)
{
	CLR_BIT(UCSRA_REGISTER,U2X_BIT);
	/* return MUART_DONE; */
}

/* Multi-processor Communication Mode */
void MUART_voidEnableMultiProcessor(void)
{
	SET_BIT(UCSRA_REGISTER,MPCM_BIT);
	/* return MUART_DONE; */
}
void MUART_voidDisableMultiProcessor(void)
{
	CLR_BIT(UCSRA_REGISTER,MPCM_BIT);
	/* return MUART_DONE; */
}

/* Receive Character */
u8   MUART_u8RXChar(void)
{
	while(!GET_BIT(UCSRA_REGISTER,RXC_BIT));
//	SET_BIT(UCSRA_Register,RXC_BIT);
	return UDR_REGISTER;
}

/* Send Data Synchronous */
void MUART_voidSendDataSynch(pu8 Copy_pu8Data)
{
	while (*Copy_pu8Data)
	{
		while(GET_BIT(UCSRA_REGISTER,UDRE_BIT) == MUART_0);
		UDR_REGISTER = *Copy_pu8Data;
		Copy_pu8Data++;
	}
	/* return MUART_DONE; */
}

/* Receive Data Synchronous */
void MUART_voidReceiveDataSynch(pu8 Copy_pu8Data, u32 Copy_u32TimeOut)
{
	u32 Local_u32TimeOutCounter = MUART_0;
	*Copy_pu8Data               = MUART_0;
	
	while (GET_BIT(UCSRA_REGISTER,RXC_BIT) == MUART_0)
	{
		Local_u32TimeOutCounter++;
		if (Local_u32TimeOutCounter == Copy_u32TimeOut)
		{
			*Copy_pu8Data = MUART_255;
			break;
		}
	}
	if (*Copy_pu8Data == MUART_0)
	{
		*Copy_pu8Data = UDR_REGISTER;
	}
	else
	{
		/* Do Nothing */
	}
	/* return MUART_DONE; */
}

/* Receive Data Synchronous with Data Length */
void MUART_voidReceiveDataSynchWithDataLength(pu8 Copy_pu8Data, u8 Copy_u8DataLength)
{
	while (Copy_u8DataLength--)
	{
		while(GET_BIT(UCSRA_REGISTER,RXC_BIT) == MUART_0);
		*Copy_pu8Data = UDR_REGISTER;
		Copy_pu8Data++;
	}
	/* return MUART_DONE; */
}

/* Receive Data Synchronous Conditional */
u8   MUART_u8ReceiveDataConditional(pu8 Copy_pu8Data)
{
	u8 Local_u8ErrorCode = MUART_1;
	if (GET_BIT(UCSRA_REGISTER,RXC_BIT) == MUART_1)
	{
		*Copy_pu8Data = UDR_REGISTER;
	}
	else
	{
		Local_u8ErrorCode = MUART_0;
	}

	return Local_u8ErrorCode;
}
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/ 
