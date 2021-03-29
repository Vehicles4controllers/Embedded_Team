/***************************************************************************************************************************************************/
/*                                                                   DIO Driver                                                                    */
/* File Name : DIO_interface.h 																		    										   */
/* Auhor     : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.1.0																			 	    										   */
/* Date      : 14 AUG 2020 																	 	    											   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : MCAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef DIO_INRERFACE_H
#define DIO_INRERFACE_H

/***************************************************************************************************************************************************/ 
/*                                                                  Macros/Enums																   */
/***************************************************************************************************************************************************/
/* Ports */
typedef enum 
{
	PORTA,				// 0
	PORTB,		       	// 1
	PORTC,	    	   	// 2
	PORTD           	// 3
}MDIO_PORT_Type;

/* Pins */	
typedef enum	
{	
	PIN0,				// 0
	PIN1,		       	// 1
	PIN2,	    	   	// 2
	PIN3,	       		// 3
	PIN4,	    	   	// 4
	PIN5,	  	     	// 5
	PIN6,	       		// 6
	PIN7            	// 7
}MDIO_PIN_Type;

/* Objects Like Macro  */
/* Port Directions Options */
#define INPUT_ALL  		0x00
#define OUTPUT_ALL 		0xFF

/* Pin Directions Options */	
#define INPUT  			0
#define OUTPUT 			1

/* Port Mode Options for Input */
#define FLOATING_ALL	0x00
#define PULLUP_ALL	    0xFF

/* Pin Mode Options for Input */
#define FLOATING	  	0
#define PULLUP		    1

/* Port Value Options for Output */	
#define LOW_ALL    		0x00
#define HIGH_ALL   		0xFF

/* Pin Value Options for Output */	
#define LOW    			0
#define HIGH   			1
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/ 
/*                                                              Functions Declaration															   */
/***************************************************************************************************************************************************/
/* Initialization */
void MDIO_voidInit             (void);

/* IO Pins */
void MDIO_voidSetPinDirection  (MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin, u8 Copy_u8Direction);
void MDIO_voidSetPinValue      (MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin, u8 Copy_u8Value); 			// Output-->Value | Input-->Mode
void MDIO_voidTogglePinValue   (MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin);
u8   MDIO_u8GetPinValue        (MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin);

/* IO Ports */
void MDIO_voidSetPortDirection (MDIO_PORT_Type Copy_Port, u8 Copy_u8Direction);
void MDIO_voidSetPortValue     (MDIO_PORT_Type Copy_Port, u8 Copy_u8Value);										// Output-->Value | Input-->Mode
void MDIO_voidTogglePortValue  (MDIO_PORT_Type Copy_Port);
u8   MDIO_u8GetPortValue       (MDIO_PORT_Type Copy_Port);
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/