/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_private.h 																		    										   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																			 	    										   */
/* Date      : 14 AUG 2020 																	 	    											   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

/***************************************************************************************************************************************************/ 
/*                                                              Registers Definitions 															   */
/* Register Summary : Page 299																													   */
/***************************************************************************************************************************************************/
#define UDR_REGISTER 		*((pu8)0x2C)	// USART I/O Data Register
#define UCSRA_REGISTER 		*((pu8)0x2B)    // USART Control and Status Register A
#define UCSRB_REGISTER 		*((pu8)0x2A)    // USART Control and Status Register B
#define UCSRC_REGISTER 		*((pu8)0x40)    // USART Control and Status Register C
#define UBRRL_REGISTER  	*((pu8)0x29)    // USART Baud Rate Registers
#define UBRRH_REGISTER 		*((pu8)0x40)	// USART Baud Rate Registers
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                                 Registers Bits 			     												   */
/* DIO Registers : Page 157      			    																								   */
/***************************************************************************************************************************************************/
/* USART Control and Status Register A - UCSRA */
#define RXC_BIT	           	7				// USART Receive Complete
#define TXC_BIT           	6				// USART Transmit Complete
#define UDRE_BIT           	5				// USART Data Register Empty
#define FE_BIT          	4				// Frame Error
#define DOR_BIT           	3				// Data OverRun
#define PE_BIT            	2				// Parity Error
#define	U2X_BIT    	    	1				// Double the USART Transmission Speed
#define MPCM_BIT			0				// Multi-processor Communication Mode

/* USART Control and Status Register B - UCSRB */
#define RXCIE_BIT	        7				// RX Complete Interrupt Enable
#define TXCIE_BIT           6				// TX Complete Interrupt Enable
#define UDRIE_BIT           5				// USART Data Register Empty Interrupt Enable
#define RXEN_BIT          	4				// Receiver Enable
#define TXEN_BIT           	3				// Transmitter Enable
#define UCSZ2_BIT           2				// Character Size
#define	RXB8_BIT    	    1				// Receive Data Bit 8
#define TXB8_BIT			0				// Transmit Data Bit 8

/* USART Control and Status Register C - UCSRC
Register Select					   UMSEL Bit Settings	
---------------------------------- --------------------------------------
| URSEL_BIT | Accessing Register | | UMSEL_BIT | Mode  				 |
---------------------------------- --------------------------------------
|     0		| UBRRH_Register	 | |     0		| Asynchronous Operation |
|     1		| UCSRC_Register	 | |     1		| Synchronous Operation  |
---------------------------------- --------------------------------------
UPM Bits Settings							   USBS Bit Settings
---------------------------------------------- --------------------------
| UPM1_BIT | UPM0_BIT | Parity Mode  	 	 | | USBS_BIT | Stop Bit(s) |
---------------------------------------------- --------------------------
|     0	   |     0	  | Disabled  		   	 | |     0	   | 1-bit 	    |
|     0	   |     1	  | Reserved			 | |     1	   | 2-bit 	    |
|     1	   |     0	  | Enabled, Even Parity | --------------------------
|     1	   |     1	  | Enabled, Odd Parity  |
----------------------------------------------
UCSZ Bits Settings
------------------------------------------------------
| UCSZ2_BIT | UCSZ1_BIT | UCSZ0_BIT | Character Size |
------------------------------------------------------
|	  0		|     0		|     0		| 5-bit  		 |
|     0		|     0		|     1		| 6-bit			 |
|     0		|     1		|     0		| 7-bit 		 |
|     0		|     1		|     1		| 8-bit 		 |
|     1		|     0		|     0		| Reserved 		 |
|     1		|     0		|     1		| Reserved 		 |
|     1		|     1		|     0		| Reserved 		 |
|     1		|     1		|     1		| 9-bit 		 |
------------------------------------------------------
Clock Polarity
----------------------------------------------------------------
| UCPOL_BIT | Transmitted Data Changed | Received Data Sampled |
----------------------------------------------------------------
|     0		| Rising XCK Edge		   | Falling XCK Edge  	   |
|     1		| Falling XCK Edge		   | Rising XCK Edge	   |
----------------------------------------------------------------*/
#define URSEL_BIT	        7				// Register Select
#define UMSEL_BIT           6				// USART Mode Select
#define UPM1_BIT	        5				// Parity Mode
#define UPM0_BIT          	4				// Parity Mode
#define USBS_BIT           	3				// Stop Bit Select
#define UCSZ1_BIT           2				// Character Size
#define	UCSZ0_BIT    	    1				// Character Size
#define UCPOL_BIT			0				// Clock Polarity

/* USART Baud Rate Registers - UBRRL and UBRRH | Page(162) */
#define UBRR11_BIT	        3				// UBRRH | USART Baud Rate Register
#define UBRR10_BIT	        2				// UBRRH | USART Baud Rate Register
#define UBRR9_BIT	        1				// UBRRH | USART Baud Rate Register
#define UBRR8_BIT	        0				// UBRRH | USART Baud Rate Register
#define UBRR7_BIT	        7				// UBRRL | USART Baud Rate Register
#define UBRR6_BIT          	6				// UBRRL | USART Baud Rate Register
#define UBRR5_BIT	        5				// UBRRL | USART Baud Rate Register
#define UBRR4_BIT          	4				// UBRRL | USART Baud Rate Register
#define UBRR3_BIT          	3				// UBRRL | USART Baud Rate Register
#define UBRR2_BIT           2				// UBRRL | USART Baud Rate Register
#define	UBRR1_BIT    	    1				// UBRRL | USART Baud Rate Register
#define UBRR0_BIT			0				// UBRRL | USART Baud Rate Register
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/  
/*                                                                     Private															       	   */
/***************************************************************************************************************************************************/
/* Magic Numbers */
#define MUART_INITIAL_VALUE 		0
#define MUART_0		 				0X00
#define MUART_0X80		 			0X80
#define MUART_1		 				1
#define MUART_8		 				8
#define MUART_255		 			255
	
/* DIO */		
#define MUART_PORT					PORTD
#define MUART_RXD					PIN0
#define MUART_TXD					PIN1

/* UART State Type */
#define MUART_DISABLE				0
#define MUART_ENABLE				1

/* Data Length Type */
#define MUART_DATA_5BIT				0x80
#define MUART_DATA_6BIT				0x82
#define MUART_DATA_7BIT				0x84
#define MUART_DATA_8BIT				0x86
#define MUART_DATA_9BIT				0x87

/* Parity Type */
#define MUART_NO_PARITY  			0x80
#define MUART_EVEN_PARITY			0xA0
#define MUART_ODD_PARITY			0xB0

/* Stop Bits Type */                
#define MUART_STOP_1BIT				0x80
#define MUART_STOP_2BITS			0x81

/* RT Control Type */
#define MUART_ENABLE_RECEIVER   	0
#define MUART_ENABLE_TRANSMITTER	1
#define MUART_ENABLE_BOTH			2

/* Mode */
#define MUART_ASYNCHRONOUS		   	0x80
#define MUART_SYNCHRONOUS			0xC0

/* Baud Rate */
#define MUART_UBRRL_Full	        0XFF

/* Clock Polarity */
#define MUART_RISING_TX			   	0x80
#define MUART_RISING_RX				0x81
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                  Return Value                                                                   */
/***************************************************************************************************************************************************/
#define MUART_DONE      			0x01
#define MUART_WRONG_INT	    		0x81  
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/
