/***************************************************************************************************************************************************/
/*                                                                   DIO Driver                                                                    */
/* File Name : DIO_config.h 																		    										   */
/* Auhor     : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.1.0																			 	    										   */
/* Date      : 14 AUG 2020 																	 	    											   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef DIO_CONFIG_H
#define DIO_CONFIG_H

/***************************************************************************************************************************************************/ 
/*                                                                 Configuration															       */
/* DIO Registers : Page 62      			    																								   */
/***************************************************************************************************************************************************/
/* MDIO_PORTx_PINx_DIR Opitions:				INPUT  
												OUTPUT 
								
   MDIO_PORTx_PINx_VALUE Options for Output:	LOW
												HIGH	

   MDIO_PORTx_PINx_MODE Opitions for Input:		FLOATING
												PULLUP		*/
										
/* PORTA - PIN0 */
#define MDIO_PORTA_PIN0_DIR		INPUT
#define MDIO_PORTA_PIN0_VALUE 	HIGH
#define MDIO_PORTA_PIN0_MODE	PULLUP

/* PORTA - PIN1 */
#define MDIO_PORTA_PIN1_DIR   	INPUT
#define MDIO_PORTA_PIN1_VALUE 	HIGH
#define MDIO_PORTA_PIN1_MODE  	PULLUP
	
/* PORTA - PIN2 */	
#define MDIO_PORTA_PIN2_DIR   	INPUT
#define MDIO_PORTA_PIN2_VALUE 	HIGH
#define MDIO_PORTA_PIN2_MODE  	PULLUP
	
/* PORTA - PIN3 */	
#define MDIO_PORTA_PIN3_DIR   	INPUT
#define MDIO_PORTA_PIN3_VALUE 	HIGH
#define MDIO_PORTA_PIN3_MODE  	PULLUP
	
/* PORTA - PIN4 */	
#define MDIO_PORTA_PIN4_DIR   	INPUT
#define MDIO_PORTA_PIN4_VALUE 	HIGH
#define MDIO_PORTA_PIN4_MODE  	PULLUP
	
/* PORTA - PIN5 */	
#define MDIO_PORTA_PIN5_DIR   	INPUT
#define MDIO_PORTA_PIN5_VALUE 	HIGH
#define MDIO_PORTA_PIN5_MODE  	PULLUP
	
/* PORTA - PIN6 */	
#define MDIO_PORTA_PIN6_DIR   	INPUT
#define MDIO_PORTA_PIN6_VALUE 	HIGH
#define MDIO_PORTA_PIN6_MODE  	PULLUP
	
/* PORTA - PIN7 */	
#define MDIO_PORTA_PIN7_DIR   	INPUT
#define MDIO_PORTA_PIN7_VALUE 	HIGH
#define MDIO_PORTA_PIN7_MODE  	PULLUP
	
/* PORTB - PIN0 */	
#define MDIO_PORTB_PIN0_DIR   	INPUT
#define MDIO_PORTB_PIN0_VALUE 	HIGH
#define MDIO_PORTB_PIN0_MODE  	PULLUP
	
/* PORTB - PIN1 */	
#define MDIO_PORTB_PIN1_DIR   	INPUT
#define MDIO_PORTB_PIN1_VALUE 	HIGH
#define MDIO_PORTB_PIN1_MODE  	PULLUP
	
/* PORTB - PIN2 */	
#define MDIO_PORTB_PIN2_DIR   	INPUT
#define MDIO_PORTB_PIN2_VALUE 	HIGH
#define MDIO_PORTB_PIN2_MODE  	PULLUP
	
/* PORTB - PIN3 */	
#define MDIO_PORTB_PIN3_DIR   	INPUT
#define MDIO_PORTB_PIN3_VALUE 	HIGH
#define MDIO_PORTB_PIN3_MODE  	PULLUP
	
/* PORTB - PIN4 */	
#define MDIO_PORTB_PIN4_DIR   	INPUT
#define MDIO_PORTB_PIN4_VALUE 	HIGH
#define MDIO_PORTB_PIN4_MODE  	PULLUP
	
/* PORTB - PIN5 */	
#define MDIO_PORTB_PIN5_DIR   	INPUT
#define MDIO_PORTB_PIN5_VALUE 	HIGH
#define MDIO_PORTB_PIN5_MODE  	PULLUP
	
/* PORTB - PIN6 */	
#define MDIO_PORTB_PIN6_DIR   	INPUT
#define MDIO_PORTB_PIN6_VALUE 	HIGH
#define MDIO_PORTB_PIN6_MODE  	PULLUP
	
/* PORTB - PIN7 */	
#define MDIO_PORTB_PIN7_DIR   	INPUT
#define MDIO_PORTB_PIN7_VALUE 	HIGH
#define MDIO_PORTB_PIN7_MODE  	PULLUP
	
/* PORTC - PIN0 */	
#define MDIO_PORTC_PIN0_DIR   	INPUT
#define MDIO_PORTC_PIN0_VALUE 	HIGH
#define MDIO_PORTC_PIN0_MODE  	PULLUP
	
/* PORTC - PIN1 */	
#define MDIO_PORTC_PIN1_DIR   	INPUT
#define MDIO_PORTC_PIN1_VALUE 	HIGH
#define MDIO_PORTC_PIN1_MODE  	PULLUP
	
/* PORTC - PIN2 */	
#define MDIO_PORTC_PIN2_DIR   	INPUT
#define MDIO_PORTC_PIN2_VALUE 	HIGH
#define MDIO_PORTC_PIN2_MODE  	PULLUP
	
/* PORTC - PIN3 */	
#define MDIO_PORTC_PIN3_DIR   	INPUT
#define MDIO_PORTC_PIN3_VALUE 	HIGH
#define MDIO_PORTC_PIN3_MODE  	PULLUP
	
/* PORTC - PIN4 */	
#define MDIO_PORTC_PIN4_DIR   	INPUT
#define MDIO_PORTC_PIN4_VALUE 	HIGH
#define MDIO_PORTC_PIN4_MODE  	PULLUP
	
/* PORTC - PIN5 */	
#define MDIO_PORTC_PIN5_DIR   	INPUT
#define MDIO_PORTC_PIN5_VALUE 	HIGH
#define MDIO_PORTC_PIN5_MODE  	PULLUP
	
/* PORTC - PIN6 */	
#define MDIO_PORTC_PIN6_DIR   	INPUT
#define MDIO_PORTC_PIN6_VALUE 	HIGH
#define MDIO_PORTC_PIN6_MODE  	PULLUP
	
/* PORTC - PIN7 */	
#define MDIO_PORTC_PIN7_DIR   	INPUT
#define MDIO_PORTC_PIN7_VALUE 	HIGH
#define MDIO_PORTC_PIN7_MODE  	PULLUP
	
/* PORTD - PIN0 */	
#define MDIO_PORTD_PIN0_DIR   	INPUT
#define MDIO_PORTD_PIN0_VALUE 	HIGH
#define MDIO_PORTD_PIN0_MODE  	PULLUP
	
/* PORTD - PIN1 */	
#define MDIO_PORTD_PIN1_DIR   	INPUT
#define MDIO_PORTD_PIN1_VALUE 	HIGH
#define MDIO_PORTD_PIN1_MODE  	PULLUP
	
/* PORTD - PIN2 */	
#define MDIO_PORTD_PIN2_DIR   	INPUT
#define MDIO_PORTD_PIN2_VALUE 	HIGH
#define MDIO_PORTD_PIN2_MODE  	PULLUP
	
/* PORTD - PIN3 */	
#define MDIO_PORTD_PIN3_DIR   	INPUT
#define MDIO_PORTD_PIN3_VALUE 	HIGH
#define MDIO_PORTD_PIN3_MODE  	PULLUP
	
/* PORTD - PIN4 */	
#define MDIO_PORTD_PIN4_DIR   	INPUT
#define MDIO_PORTD_PIN4_VALUE 	HIGH
#define MDIO_PORTD_PIN4_MODE  	PULLUP
	
/* PORTD - PIN5 */	
#define MDIO_PORTD_PIN5_DIR   	INPUT
#define MDIO_PORTD_PIN5_VALUE 	HIGH
#define MDIO_PORTD_PIN5_MODE  	PULLUP
	
/* PORTD - PIN6 */	
#define MDIO_PORTD_PIN6_DIR   	INPUT
#define MDIO_PORTD_PIN6_VALUE 	HIGH
#define MDIO_PORTD_PIN6_MODE  	PULLUP
	
/* PORTD - PIN7 */	
#define MDIO_PORTD_PIN7_DIR   	INPUT
#define MDIO_PORTD_PIN7_VALUE 	HIGH
#define MDIO_PORTD_PIN7_MODE  	PULLUP
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                                	   Errors                                                                	   */
/***************************************************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|													Errors				  | Return Value														  |*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|													MDIO_DONE (No-Errors) | 	0x01															  |*/
/*|                                                 MDIO_WRONG_PORT 	  | 	0x81			                                                  |*/
/*|                                                 MDIO_WRONG_PIN        | 	0x82			                                                  |*/
/*|                                                 MDIO_WRONG_DIRECTION  | 	0x84			                                                  |*/
/*|                                                 MDIO_WRONG_VALUE      | 	0x88			                                                  |*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/***************************************************************************************************************************************************/ 

#endif
/***************************************************************************************************************************************************/