/***************************************************************************************************************************************************/
/*                                                                   DIO Driver                                                                    */
/* File Name : DIO_private.h 																		    										   */
/* Auhor     : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.1.0																			 	    										   */
/* Date      : 14 AUG 2020 																	 	    											   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/***************************************************************************************************************************************************/ 
/*                                                              Registers Definitions 															   */
/* Register Summary : Page 299																													   */
/***************************************************************************************************************************************************/ 
/* DIO PORT A Registers */
#define PORTA_REGISTER  		*((volatile pu8)0x3B)	// Port A Data Register – PORTA
#define DDRA_REGISTER   		*((volatile pu8)0x3A)	// Port A Data Direction Register – DDRA
#define PINA_REGISTER   		*((volatile pu8)0x39)	// Port A Input Pins Address – PINA
	
/* DIO PORT B Registers */	
#define PORTB_REGISTER  		*((volatile pu8)0x38)	// Port B Data Register – PORTB
#define DDRB_REGISTER   		*((volatile pu8)0x37)  	// Port B Data Direction Register – DDRB
#define PINB_REGISTER   		*((volatile pu8)0x36)	// Port B Input Pins Address – PINB
	
/* DIO PORT C Registers */	
#define PORTC_REGISTER  		*((volatile pu8)0x35)	// Port C Data Register – PORTC
#define DDRC_REGISTER   		*((volatile pu8)0x34)	// Port C Data Direction Register – DDRC
#define PINC_REGISTER   		*((volatile pu8)0x33)	// Port C Input Pins Address – PINC
	
/* DIO PORT D Registers */	
#define PORTD_REGISTER  		*((volatile pu8)0x32)	// Port D Data Register – PORTD
#define DDRD_REGISTER   		*((volatile pu8)0x31)	// Port D Data Direction Register – DDRD
#define PIND_REGISTER   		*((volatile pu8)0x30)	// Port D Input Pins Address – PIND
	
/* Other Registers *//*	
#define SFIOR_REGISTER   		*((volatile pu8)0x50)	// Special Function I/O Register – SFIOR | To disable the pull-ups in the I/O ports */
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/ 
/*                                                                 Registers Bits 			     												   */
/* DIO Registers : Page 62      			    																								   */
/***************************************************************************************************************************************************/
/* Different DIO Pin States
----------------------------------------
| DDR_BIT | PORT_BIT | PIN State	   |
----------------------------------------
|    0	  |     0	 | Input Floating  |
|	 0	  |     1	 | Input Pulled Up |
|	 1	  |	    0	 | Output Low	   |
|	 1    |	    1	 | Output High	   |
---------------------------------------- */

/* Special Function I/O Register – SFIOR | To disable the pull-ups in the I/O ports
---------------------------------------------------
| DDR_BIT | PORT_BIT | PUD_BIT | I/O    | Pull-up |
---------------------------------------------------
|    0	  |     0	 | 	  0    | Input  |   NO	  |
|	 0	  |     1	 | 	  0	   | Input  |	Yes   |
|	 1	  |	    X	 | 	  1	   | Input  |   No    |
|	 1    |	    X	 | 	  X    | Output |    -    |
--------------------------------------------------- *//*
#define PUD_BIT					2*/
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/  
/*                                                                     Private															       	   */
/***************************************************************************************************************************************************/
/* Magic Numbers */
#define MDIO_INITIAL_VALUE 		0

/* PORTA - PIN0 */
#if   (MDIO_PORTA_PIN0_DIR == INPUT) &&(MDIO_PORTA_PIN0_MODE == PULLUP)
	#define MDIO_PORTA_PIN0_VALUE HIGH
#elif (MDIO_PORTA_PIN0_DIR == INPUT) &&(MDIO_PORTA_PIN0_MODE == FLOATING)
	#define MDIO_PORTA_PIN0_VALUE LOW
#endif

/* PORTA - PIN1 */
#if   (MDIO_PORTA_PIN1_DIR == INPUT) &&(MDIO_PORTA_PIN1_MODE == PULLUP)
	#define MDIO_PORTA_PIN1_VALUE HIGH
#elif (MDIO_PORTA_PIN1_DIR == INPUT) &&(MDIO_PORTA_PIN1_MODE == FLOATING)
	#define MDIO_PORTA_PIN1_VALUE LOW
#endif

/* PORTA - PIN2 */
#if   (MDIO_PORTA_PIN2_DIR == INPUT) &&(MDIO_PORTA_PIN2_MODE == PULLUP)
	#define MDIO_PORTA_PIN2_VALUE HIGH
#elif (MDIO_PORTA_PIN2_DIR == INPUT) &&(MDIO_PORTA_PIN2_MODE == FLOATING)
	#define MDIO_PORTA_PIN2_VALUE LOW
#endif

/* PORTA - PIN3 */
#if   (MDIO_PORTA_PIN3_DIR == INPUT) &&(MDIO_PORTA_PIN3_MODE == PULLUP)
	#define MDIO_PORTA_PIN3_VALUE HIGH
#elif (MDIO_PORTA_PIN3_DIR == INPUT) &&(MDIO_PORTA_PIN3_MODE == FLOATING)
	#define MDIO_PORTA_PIN3_VALUE LOW
#endif

/* PORTA - PIN4 */
#if   (MDIO_PORTA_PIN4_DIR == INPUT) &&(MDIO_PORTA_PIN4_MODE == PULLUP)
	#define MDIO_PORTA_PIN4_VALUE HIGH
#elif (MDIO_PORTA_PIN4_DIR == INPUT) &&(MDIO_PORTA_PIN4_MODE == FLOATING)
	#define MDIO_PORTA_PIN4_VALUE LOW
#endif

/* PORTA - PIN5 */
#if   (MDIO_PORTA_PIN5_DIR == INPUT) &&(MDIO_PORTA_PIN5_MODE == PULLUP)
	#define MDIO_PORTA_PIN5_VALUE HIGH
#elif (MDIO_PORTA_PIN5_DIR == INPUT) &&(MDIO_PORTA_PIN5_MODE == FLOATING)
	#define MDIO_PORTA_PIN5_VALUE LOW
#endif

/* PORTA - PIN6 */
#if   (MDIO_PORTA_PIN6_DIR == INPUT) &&(MDIO_PORTA_PIN6_MODE == PULLUP)
	#define MDIO_PORTA_PIN6_VALUE HIGH
#elif (MDIO_PORTA_PIN6_DIR == INPUT) &&(MDIO_PORTA_PIN6_MODE == FLOATING)
	#define MDIO_PORTA_PIN6_VALUE LOW
#endif

/* PORTA - PIN7 */
#if   (MDIO_PORTA_PIN7_DIR == INPUT) &&(MDIO_PORTA_PIN7_MODE == PULLUP)
	#define MDIO_PORTA_PIN7_VALUE HIGH
#elif (MDIO_PORTA_PIN7_DIR == INPUT) &&(MDIO_PORTA_PIN7_MODE == FLOATING)
	#define MDIO_PORTA_PIN7_VALUE LOW
#endif

/* PORTB - PIN0 */
#if (MDIO_PORTB_PIN0_DIR == INPUT) &&(MDIO_PORTB_PIN0_MODE == PULLUP)
	#define MDIO_PORTB_PIN0_VALUE HIGH
#elif (MDIO_PORTB_PIN0_DIR == INPUT) &&(MDIO_PORTB_PIN0_MODE == FLOATING)
	#define MDIO_PORTB_PIN0_VALUE LOW
#endif

/* PORTB - PIN1 */
#if   (MDIO_PORTB_PIN1_DIR == INPUT) &&(MDIO_PORTB_PIN1_MODE == PULLUP)
	#define MDIO_PORTB_PIN1_VALUE HIGH
#elif (MDIO_PORTB_PIN1_DIR == INPUT) &&(MDIO_PORTB_PIN1_MODE == FLOATING)
	#define MDIO_PORTB_PIN1_VALUE LOW
#endif

/* PORTB - PIN2 */
#if   (MDIO_PORTB_PIN2_DIR == INPUT) &&(MDIO_PORTB_PIN2_MODE == PULLUP)
	#define MDIO_PORTB_PIN2_VALUE HIGH
#elif (MDIO_PORTB_PIN2_DIR == INPUT) &&(MDIO_PORTB_PIN2_MODE == FLOATING)
	#define MDIO_PORTB_PIN2_VALUE LOW
#endif

/* PORTB - PIN3 */
#if   (MDIO_PORTB_PIN3_DIR == INPUT) &&(MDIO_PORTB_PIN3_MODE == PULLUP)
	#define MDIO_PORTB_PIN3_VALUE HIGH
#elif (MDIO_PORTB_PIN3_DIR == INPUT) &&(MDIO_PORTB_PIN3_MODE == FLOATING)
	#define MDIO_PORTB_PIN3_VALUE LOW
#endif

/* PORTB - PIN4 */
#if   (MDIO_PORTB_PIN4_DIR == INPUT) &&(MDIO_PORTB_PIN4_MODE == PULLUP)
	#define MDIO_PORTB_PIN4_VALUE HIGH
#elif (MDIO_PORTB_PIN4_DIR == INPUT) &&(MDIO_PORTB_PIN4_MODE == FLOATING)
	#define MDIO_PORTB_PIN4_VALUE LOW
#endif

/* PORTB - PIN5 */
#if   (MDIO_PORTB_PIN5_DIR == INPUT) &&(MDIO_PORTB_PIN5_MODE == PULLUP)
	#define MDIO_PORTB_PIN5_VALUE HIGH
#elif (MDIO_PORTB_PIN5_DIR == INPUT) &&(MDIO_PORTB_PIN5_MODE == FLOATING)
	#define MDIO_PORTB_PIN5_VALUE LOW
#endif

/* PORTB - PIN6 */
#if   (MDIO_PORTB_PIN6_DIR == INPUT) &&(MDIO_PORTB_PIN6_MODE == PULLUP)
	#define MDIO_PORTB_PIN6_VALUE HIGH
#elif (MDIO_PORTB_PIN6_DIR == INPUT) &&(MDIO_PORTB_PIN6_MODE == FLOATING)
	#define MDIO_PORTB_PIN6_VALUE LOW
#endif

/* PORTB - PIN7 */
#if   (MDIO_PORTB_PIN7_DIR == INPUT) &&(MDIO_PORTB_PIN7_MODE == PULLUP)
	#define MDIO_PORTB_PIN7_VALUE HIGH
#elif (MDIO_PORTB_PIN7_DIR == INPUT) &&(MDIO_PORTB_PIN7_MODE == FLOATING)
	#define MDIO_PORTB_PIN7_VALUE LOW
#endif

/* PORTC - PIN0 */
#if   (MDIO_PORTC_PIN0_DIR == INPUT) &&(MDIO_PORTC_PIN0_MODE == PULLUP)
	#define MDIO_PORTC_PIN0_VALUE HIGH
#elif (MDIO_PORTC_PIN0_DIR == INPUT) &&(MDIO_PORTC_PIN0_MODE == FLOATING)
	#define MDIO_PORTC_PIN0_VALUE LOW
#endif

/* PORTC - PIN1 */
#if   (MDIO_PORTC_PIN1_DIR == INPUT) &&(MDIO_PORTC_PIN1_MODE == PULLUP)
	#define MDIO_PORTC_PIN1_VALUE HIGH
#elif (MDIO_PORTC_PIN1_DIR == INPUT) &&(MDIO_PORTC_PIN1_MODE == FLOATING)
	#define MDIO_PORTC_PIN1_VALUE LOW
#endif

/* PORTC - PIN2 */
#if   (MDIO_PORTC_PIN2_DIR == INPUT) &&(MDIO_PORTC_PIN2_MODE == PULLUP)
	#define MDIO_PORTC_PIN2_VALUE HIGH
#elif (MDIO_PORTC_PIN2_DIR == INPUT) &&(MDIO_PORTC_PIN2_MODE == FLOATING)
	#define MDIO_PORTC_PIN2_VALUE LOW
#endif

/* PORTC - PIN3 */
#if   (MDIO_PORTC_PIN3_DIR == INPUT) &&(MDIO_PORTC_PIN3_MODE == PULLUP)
	#define MDIO_PORTC_PIN3_VALUE HIGH
#elif (MDIO_PORTC_PIN3_DIR == INPUT) &&(MDIO_PORTC_PIN3_MODE == FLOATING)
	#define MDIO_PORTC_PIN3_VALUE LOW
#endif

/* PORTC - PIN4 */
#if   (MDIO_PORTC_PIN4_DIR == INPUT) &&(MDIO_PORTC_PIN4_MODE == PULLUP)
	#define MDIO_PORTC_PIN4_VALUE HIGH
#elif (MDIO_PORTC_PIN4_DIR == INPUT) &&(MDIO_PORTC_PIN4_MODE == FLOATING)
	#define MDIO_PORTC_PIN4_VALUE LOW
#endif

/* PORTC - PIN5 */
#if   (MDIO_PORTC_PIN5_DIR == INPUT) &&(MDIO_PORTC_PIN5_MODE == PULLUP)
	#define MDIO_PORTC_PIN5_VALUE HIGH
#elif (MDIO_PORTC_PIN5_DIR == INPUT) &&(MDIO_PORTC_PIN5_MODE == FLOATING)
	#define MDIO_PORTC_PIN5_VALUE LOW
#endif

/* PORTC - PIN6 */
#if   (MDIO_PORTC_PIN6_DIR == INPUT) &&(MDIO_PORTC_PIN6_MODE == PULLUP)
	#define MDIO_PORTC_PIN6_VALUE HIGH
#elif (MDIO_PORTC_PIN6_DIR == INPUT) &&(MDIO_PORTC_PIN6_MODE == FLOATING)
	#define MDIO_PORTC_PIN6_VALUE LOW
#endif

/* PORTC - PIN7 */
#if   (MDIO_PORTC_PIN7_DIR == INPUT) &&(MDIO_PORTC_PIN7_MODE == PULLUP)
	#define MDIO_PORTC_PIN7_VALUE HIGH
#elif (MDIO_PORTC_PIN7_DIR == INPUT) &&(MDIO_PORTC_PIN7_MODE == FLOATING)
	#define MDIO_PORTC_PIN7_VALUE LOW
#endif

/* PORTD - PIN0 */
#if   (MDIO_PORTD_PIN0_DIR == INPUT) &&(MDIO_PORTD_PIN0_MODE == PULLUP)
	#define MDIO_PORTD_PIN0_VALUE HIGH
#elif (MDIO_PORTD_PIN0_DIR == INPUT) &&(MDIO_PORTD_PIN0_MODE == FLOATING)
	#define MDIO_PORTD_PIN0_VALUE LOW
#endif

/* PORTD - PIN1 */
#if   (MDIO_PORTD_PIN1_DIR == INPUT) &&(MDIO_PORTD_PIN1_MODE == PULLUP)
	#define MDIO_PORTD_PIN1_VALUE HIGH
#elif (MDIO_PORTD_PIN1_DIR == INPUT) &&(MDIO_PORTD_PIN1_MODE == FLOATING)
	#define MDIO_PORTD_PIN1_VALUE LOW
#endif

/* PORTD - PIN2 */
#if   (MDIO_PORTD_PIN2_DIR == INPUT) &&(MDIO_PORTD_PIN2_MODE == PULLUP)
	#define MDIO_PORTD_PIN2_VALUE HIGH
#elif (MDIO_PORTD_PIN2_DIR == INPUT) &&(MDIO_PORTD_PIN2_MODE == FLOATING)
	#define MDIO_PORTD_PIN2_VALUE LOW
#endif

/* PORTD - PIN3 */
#if   (MDIO_PORTD_PIN3_DIR == INPUT) &&(MDIO_PORTD_PIN3_MODE == PULLUP)
	#define MDIO_PORTD_PIN3_VALUE HIGH
#elif (MDIO_PORTD_PIN3_DIR == INPUT) &&(MDIO_PORTD_PIN3_MODE == FLOATING)
	#define MDIO_PORTD_PIN3_VALUE LOW
#endif

/* PORTD - PIN4 */
#if   (MDIO_PORTD_PIN4_DIR == INPUT) &&(MDIO_PORTD_PIN4_MODE == PULLUP)
	#define MDIO_PORTD_PIN4_VALUE HIGH
#elif (MDIO_PORTD_PIN4_DIR == INPUT) &&(MDIO_PORTD_PIN4_MODE == FLOATING)
	#define MDIO_PORTD_PIN4_VALUE LOW
#endif

/* PORTD - PIN5 */
#if   (MDIO_PORTD_PIN5_DIR == INPUT) &&(MDIO_PORTD_PIN5_MODE == PULLUP)
	#define MDIO_PORTD_PIN5_VALUE HIGH
#elif (MDIO_PORTD_PIN5_DIR == INPUT) &&(MDIO_PORTD_PIN5_MODE == FLOATING)
	#define MDIO_PORTD_PIN5_VALUE LOW
#endif

/* PORTD - PIN6 */
#if   (MDIO_PORTD_PIN6_DIR == INPUT) &&(MDIO_PORTD_PIN6_MODE == PULLUP)
	#define MDIO_PORTD_PIN6_VALUE HIGH
#elif (MDIO_PORTD_PIN6_DIR == INPUT) &&(MDIO_PORTD_PIN6_MODE == FLOATING)
	#define MDIO_PORTD_PIN6_VALUE LOW
#endif

/* PORTD - PIN7 */
#if   (MDIO_PORTD_PIN7_DIR == INPUT) &&(MDIO_PORTD_PIN7_MODE == PULLUP)
	#define MDIO_PORTD_PIN7_VALUE HIGH
#elif (MDIO_PORTD_PIN7_DIR == INPUT) &&(MDIO_PORTD_PIN7_MODE == FLOATING)
	#define MDIO_PORTD_PIN7_VALUE LOW
#endif
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/
/*                                                                  Return Value                                                                   */
/***************************************************************************************************************************************************/
#define MDIO_DONE      			0x01 
#define MDIO_WRONG_PORT     	0x81        
#define MDIO_WRONG_PIN      	0x82 
#define MDIO_WRONG_DIRECTION	0x84 
#define MDIO_WRONG_VALUE		0x88
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/