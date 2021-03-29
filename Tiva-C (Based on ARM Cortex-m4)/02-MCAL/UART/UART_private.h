/***************************************************************************************************************************************************/
/*                                                                   UART Driver                                                                   */
/* File Name : UART_private.h 																	    											   */
/* Author    : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 18 NOV 2020 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

/***************************************************************************************************************************************************/ 
/*                                                              Registers Definitions 															   */
/* 																	    UART0 																	   */
/* Boundary address : 0x4000C000 - 0x4000CFFF															 									       */
/* 																	    UART1 																	   */
/* Boundary address : 0x4000D000 - 0x4000DFFF																 									   */
/* 																	    UART2 																	   */
/* Boundary address : 0x4000E000 - 0x4000EFFF															 									  	   */
/* 																	    UART3 																	   */
/* Boundary address : 0x4000F000 - 0x4000FFFF															 									  	   */
/* 																   	    UART4 																	   */
/* Boundary address : 0x40010000 - 0x40010FFF 														 									  	       */
/* 																        UART5 																	   */
/* Boundary address : 0x40011000 - 0x40011FFF 						    								 									  	   */
/* 																        UART6 																	   */
/* Boundary address : 0x40012000 - 0x40012FFF 														 									  	       */
/* 																	    UART7 																	   */
/* Boundary address : 0x40013000 - 0x40013FFF 														 									  	       */
/*                                                                                                                                                 */
/* Register map     : Section 																								   */ 
/***************************************************************************************************************************************************/ 
/* UART0 Base Address */
#define MUART0_BASE_ADDRESS	0x4000C000
/* UART1 Base Address */
#define MUART1_BASE_ADDRESS	0x4000D000
/* UART2 Base Address */
#define MUART2_BASE_ADDRESS	0x4000E000
/* UART3 Base Address */
#define MUART3_BASE_ADDRESS	0x4000F000
/* UART4 Base Address */
#define MUART4_BASE_ADDRESS	0x40010000
/* UART5 Base Address */
#define MUART5_BASE_ADDRESS	0x40011000
/* UART6 Base Address */
#define MUART6_BASE_ADDRESS	0x40012000
/* UART7 Base Address */
#define MUART7_BASE_ADDRESS	0x40013000

/* UART Registers */
typedef struct
{
	volatile u32 DR         ;		// UART Data (UARTDR)
	volatile u32 RSR_ECR    ;		// UART Receive Status/Error Clear (UARTRSR/UARTECR)
    volatile u32 Reserved[4];       // Reserved
	volatile u32 FR         ;		// UART Flag (UARTFR)
    volatile u32 Reserved4  ;       // Reserved
	volatile u32 ILPR       ;      	// UART IrDA Low-Power Register (UARTILPR)
	volatile u32 IBRD       ;	    // UART Integer Baud-Rate Divisor (UARTIBRD)
	volatile u32 FBRD       ;      	// UART Fractional Baud-Rate Divisor (UARTFBRD)
	volatile u32 LCRH       ;	    // UART Line Control (UARTLCRH)
	volatile u32 CTL        ;	    // UART Control (UARTCTL)
	volatile u32 IFLS       ;	    // UART Interrupt FIFO Level Select (UARTIFLS)
	volatile u32 IM         ;	    // UART Interrupt Mask (UARTIM)
	volatile u32 RIS        ;   	// UART Raw Interrupt Status (UARTRIS)
	volatile u32 MIS	    ;   	// UART Masked Interrupt Status (UARTMIS)
	volatile u32 ICR        ;   	// UART Interrupt Clear (UARTICR)
	volatile u32 DMACTL     ;   	// UART DMA Control (UARTDMACTL)
}MUART_Type;

#define RCGCUART			*(volatile pu32)0x400FE618	// Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control (RCGCUART)

#define MUART0				((volatile MUART_Type*)MUART0_BASE_ADDRESS)
#define MUART1				((volatile MUART_Type*)MUART1_BASE_ADDRESS)
#define MUART2				((volatile MUART_Type*)MUART2_BASE_ADDRESS)
#define MUART3				((volatile MUART_Type*)MUART3_BASE_ADDRESS)
#define MUART4				((volatile MUART_Type*)MUART4_BASE_ADDRESS)
#define MUART5				((volatile MUART_Type*)MUART5_BASE_ADDRESS)
#define MUART6				((volatile MUART_Type*)MUART6_BASE_ADDRESS)
#define MUART7				((volatile MUART_Type*)MUART7_BASE_ADDRESS)

volatile MUART_Type* MUART[] = 
{
	MUART0,
	MUART1,    
	MUART2,    
	MUART3,    
	MUART4,     
	MUART5,  
	MUART6,    
	MUART7    
};
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/ 
/*                                                                 Registers Bits 			     												   */
/* UART Registers : Section    																								   */
/***************************************************************************************************************************************************/ 
/* UART Flag (UARTFR) */
#define TXFE_BIT			7		// UART Transmit FIFO Empty
#define RXFF_BIT			6       // UART Receive FIFO Full
#define TXFF_BIT			5       // UART Transmit FIFO Full
#define RXFE_BIT			4       // UART Receive FIFO Empty
#define BUSY_BIT			3       // UART Busy
#define CTS_BIT				0       // Clear To Send

/* UART Line Control (UARTLCRH) */
#define SPS_BIT				7		// UART Stick Parity Select
#define WLEN1_BIT			6       // UART Word Length
#define WLEN0_BIT			5       // UART Word Length
#define FEN_BIT				4       // UART Enable FIFOs
#define STP2_BIT			3       // UART Two Stop Bits Select
#define EPS_BIT				2       // UART Even Parity Select
#define PEN_BIT				1       // UART Parity Enable
#define BRK_BIT				0       // UART Send Break

/* UART Control (UARTCTL) */ 
#define CTSEN_BIT			15		// Enable Clear To Send
#define RTSEN_BIT			14      // Enable Request to Send
#define RTS_BIT				11      // Request to Send
#define RXE_BIT				9      	// UART Receive Enable
#define TXE_BIT				8       // UART Transmit Enable
#define LBE_BIT				7       // UART Loop Back Enable
#define HSE_BIT				5       // High-Speed Enable
#define EOT_BIT				4       // End of Transmission
#define SMART_BIT			3       // ISO 7816 Smart Card Support
#define SIRLP_BIT			2       // UART SIR Low-Power Mode
#define SIREN_BIT			1		// UART SIR Enable
#define UARTEN_BIT			0       // UART Enable
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/  
/*                                                                     Private															       	   */
/***************************************************************************************************************************************************/ 
/* Magic Numbers */
#define MUART_INITIAL_VALUE 0
#define MUART_HALF		 	0.5
#define MUART_0			 	0
#define MUART_1			 	1
#define MUART_4			 	4
#define MUART_5			 	5
#define MUART_64		 	64
#define MUART_16		 	16
#define MUART_134		 	134
#define MUART_130		 	130
#define MUART_255		 	255

#define MUART_CLK_DIVIDER	16
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                 Global Variables                                                                */
/***************************************************************************************************************************************************/

struct UART_PORT
{
    gpio_port_t PORT1;
    u8 pin1;
    gpio_port_t PORT2;
    u8 pin2;
};

struct UART_PORT PINS[8] = {{PORTA,0,PORTA,1},
							{PORTB,0,PORTB,1},
							{PORTD,6,PORTD,7},
							{PORTC,6,PORTC,7},
							{PORTC,4,PORTC,5},
							{PORTE,4,PORTE,5},
							{PORTD,4,PORTD,5},
							{PORTE,0,PORTE,1}};
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                CallBack Functions                                                               */
/***************************************************************************************************************************************************/
#define NULL				((void*)0x00)
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/ 
