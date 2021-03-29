/***************************************************************************************************************************************************/
/*                                                                   DIO Driver                                                                    */
/* File Name : DIO_program.c 																	    											   */
/* Auhor     : Mahmoud Mohamed Kamal														 	    											   */
/* Version	 : 1.1.0																			 	    										   */
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

/* Own Driver Files */
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"
/***************************************************************************************************************************************************/ 

/***************************************************************************************************************************************************/
/*                                                                   Functions																	   */
/***************************************************************************************************************************************************/
/* Initialization */
void MDIO_voidInit(void)
{
	/* PORTA Direction */
	DDRA_REGISTER  = CONC(MDIO_PORTA_PIN7_DIR,
						  MDIO_PORTA_PIN6_DIR,
						  MDIO_PORTA_PIN5_DIR,
						  MDIO_PORTA_PIN4_DIR,
						  MDIO_PORTA_PIN3_DIR,
						  MDIO_PORTA_PIN2_DIR,
						  MDIO_PORTA_PIN1_DIR,
						  MDIO_PORTA_PIN0_DIR);
	/* PORTB Direction */								
	DDRB_REGISTER  = CONC(MDIO_PORTB_PIN7_DIR,
						  MDIO_PORTB_PIN6_DIR,
						  MDIO_PORTB_PIN5_DIR,
						  MDIO_PORTB_PIN4_DIR,
						  MDIO_PORTB_PIN3_DIR,
						  MDIO_PORTB_PIN2_DIR,
						  MDIO_PORTB_PIN1_DIR,
						  MDIO_PORTB_PIN0_DIR);	
	/* PORTC Direction */								
	DDRC_REGISTER  = CONC(MDIO_PORTC_PIN7_DIR,
						  MDIO_PORTC_PIN6_DIR,
						  MDIO_PORTC_PIN5_DIR,
						  MDIO_PORTC_PIN4_DIR,
						  MDIO_PORTC_PIN3_DIR,
						  MDIO_PORTC_PIN2_DIR,
						  MDIO_PORTC_PIN1_DIR,
						  MDIO_PORTC_PIN0_DIR);	
	/* PORTD Direction */								
	DDRD_REGISTER  = CONC(MDIO_PORTD_PIN7_DIR,
						  MDIO_PORTD_PIN6_DIR,
						  MDIO_PORTD_PIN5_DIR,
						  MDIO_PORTD_PIN4_DIR,
						  MDIO_PORTD_PIN3_DIR,
						  MDIO_PORTD_PIN2_DIR,
						  MDIO_PORTD_PIN1_DIR,
						  MDIO_PORTD_PIN0_DIR);
	/* PORTA Value */
	PORTA_REGISTER = CONC(MDIO_PORTA_PIN7_VALUE,
						  MDIO_PORTA_PIN6_VALUE,
						  MDIO_PORTA_PIN5_VALUE,
						  MDIO_PORTA_PIN4_VALUE,
						  MDIO_PORTA_PIN3_VALUE,
						  MDIO_PORTA_PIN2_VALUE,
						  MDIO_PORTA_PIN1_VALUE,
						  MDIO_PORTA_PIN0_VALUE);
	/* PORTB Value */
	PORTB_REGISTER = CONC(MDIO_PORTB_PIN7_VALUE,
						  MDIO_PORTB_PIN6_VALUE,
						  MDIO_PORTB_PIN5_VALUE,
						  MDIO_PORTB_PIN4_VALUE,
						  MDIO_PORTB_PIN3_VALUE,
						  MDIO_PORTB_PIN2_VALUE,
						  MDIO_PORTB_PIN1_VALUE,
						  MDIO_PORTB_PIN0_VALUE);
	/* PORTC Value */
	PORTC_REGISTER = CONC(MDIO_PORTC_PIN7_VALUE,
						  MDIO_PORTC_PIN6_VALUE,
						  MDIO_PORTC_PIN5_VALUE,
						  MDIO_PORTC_PIN4_VALUE,
						  MDIO_PORTC_PIN3_VALUE,
						  MDIO_PORTC_PIN2_VALUE,
						  MDIO_PORTC_PIN1_VALUE,
						  MDIO_PORTC_PIN0_VALUE);
	/* PORTD Value */
	PORTD_REGISTER = CONC(MDIO_PORTD_PIN7_VALUE,
						  MDIO_PORTD_PIN6_VALUE,
						  MDIO_PORTD_PIN5_VALUE,
						  MDIO_PORTD_PIN4_VALUE,
						  MDIO_PORTD_PIN3_VALUE,
						  MDIO_PORTD_PIN2_VALUE,
						  MDIO_PORTD_PIN1_VALUE,
						  MDIO_PORTD_PIN0_VALUE);
	/* PORTA Mode */
	PORTA_REGISTER = CONC(MDIO_PORTA_PIN7_MODE,
						  MDIO_PORTA_PIN6_MODE,
						  MDIO_PORTA_PIN5_MODE,
						  MDIO_PORTA_PIN4_MODE,
						  MDIO_PORTA_PIN3_MODE,
						  MDIO_PORTA_PIN2_MODE,
						  MDIO_PORTA_PIN1_MODE,
						  MDIO_PORTA_PIN0_MODE);
	/* PORTB Mode */
	PORTB_REGISTER = CONC(MDIO_PORTB_PIN7_MODE,
						  MDIO_PORTB_PIN6_MODE,
						  MDIO_PORTB_PIN5_MODE,
						  MDIO_PORTB_PIN4_MODE,
						  MDIO_PORTB_PIN3_MODE,
						  MDIO_PORTB_PIN2_MODE,
						  MDIO_PORTB_PIN1_MODE,
						  MDIO_PORTB_PIN0_MODE);
	/* PORTC Mode */
	PORTC_REGISTER = CONC(MDIO_PORTC_PIN7_MODE,
					      MDIO_PORTC_PIN6_MODE,
					      MDIO_PORTC_PIN5_MODE,
					      MDIO_PORTC_PIN4_MODE,
					      MDIO_PORTC_PIN3_MODE,
					      MDIO_PORTC_PIN2_MODE,
					      MDIO_PORTC_PIN1_MODE,
					      MDIO_PORTC_PIN0_MODE);
	/* PORTD Mode */                                
	PORTD_REGISTER = CONC(MDIO_PORTD_PIN7_MODE,
						  MDIO_PORTD_PIN6_MODE,
						  MDIO_PORTD_PIN5_MODE,
						  MDIO_PORTD_PIN4_MODE,
						  MDIO_PORTD_PIN3_MODE,
						  MDIO_PORTD_PIN2_MODE,
						  MDIO_PORTD_PIN1_MODE,
						  MDIO_PORTD_PIN0_MODE);	
	/* return MDIO_DONE; */
}


/* IO Pins */
void MDIO_voidSetPinDirection(MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin, u8 Copy_u8Direction)
{
	if (Copy_Pin <= PIN7)
	{
		switch (Copy_u8Direction)
		{
			case INPUT :
				switch (Copy_Port)
				{
					case PORTA: CLR_BIT(DDRA_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;
					case PORTB: CLR_BIT(DDRB_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;  
					case PORTC: CLR_BIT(DDRC_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;  
					case PORTD: CLR_BIT(DDRD_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;
					default   : /* return MDIO_WRONG_PORT; */ 								break;
				}
				break;
			case OUTPUT:
				switch (Copy_Port)
				{
					case PORTA: SET_BIT(DDRA_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;              
					case PORTB: SET_BIT(DDRB_REGISTER,Copy_Pin); /* return MDIO_DONE; */ 	break;              
					case PORTC: SET_BIT(DDRC_REGISTER,Copy_Pin); /* return MDIO_DONE; */ 	break;              
					case PORTD: SET_BIT(DDRD_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break; 
					default   : /* return MDIO_WRONG_PORT; */ 								break;
				}
				break;
			default    : /* return MDIO_WRONG_DIRECTION; */ 								break;
		}
	}
	else
	{
		/* return MDIO_WRONG_PIN; */ 
	}
}

void MDIO_voidSetPinValue(MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin, u8 Copy_u8Value)
{
	if (Copy_Pin <= PIN7)
	{
		switch (Copy_u8Value)
		{
			case LOW:
				switch (Copy_Port)
				{
					case PORTA: CLR_BIT(PORTA_REGISTER,Copy_Pin);	/* return MDIO_DONE; */	break;
					case PORTB: CLR_BIT(PORTB_REGISTER,Copy_Pin);	/* return MDIO_DONE; */	break;                   
					case PORTC: CLR_BIT(PORTC_REGISTER,Copy_Pin); 	/* return MDIO_DONE; */	break;                   
					case PORTD: CLR_BIT(PORTD_REGISTER,Copy_Pin);	/* return MDIO_DONE; */	break;
					default   : /* return MDIO_WRONG_PORT; */ 								break;
				}
				break;
			case HIGH:
				switch (Copy_Port)
				{
					case PORTA: SET_BIT(PORTA_REGISTER,Copy_Pin);	/* return MDIO_DONE; */	break;                   
					case PORTB: SET_BIT(PORTB_REGISTER,Copy_Pin); 	/* return MDIO_DONE; */	break;                   
					case PORTC: SET_BIT(PORTC_REGISTER,Copy_Pin); 	/* return MDIO_DONE; */	break;                   
					case PORTD: SET_BIT(PORTD_REGISTER,Copy_Pin); 	/* return MDIO_DONE; */	break;
					default   : /* return MDIO_WRONG_PORT; */ 								break;
				}
				break;
			default  : /* return MDIO_WRONG_VALUE; */ 										break;
		}
	}
	else
	{
		/* return MDIO_WRONG_PIN; */ 
	}
}

void MDIO_voidTogglePinValue(MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin)
{
	if (Copy_Pin <= PIN7)
	{
		switch (Copy_Port)
		{
			case PORTA: TOG_BIT(PORTA_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;
			case PORTB: TOG_BIT(PORTB_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;                   
			case PORTC: TOG_BIT(PORTC_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;                   
			case PORTD: TOG_BIT(PORTD_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;
			default   : /* return MDIO_WRONG_PORT; */ 								break;
		}
	}
	else
	{
		/* return MDIO_WRONG_PIN; */ 
	}
}

u8   MDIO_u8GetPinValue(MDIO_PORT_Type Copy_Port, MDIO_PIN_Type Copy_Pin)
{
	u8 Local_u8Value = MDIO_INITIAL_VALUE;
	
	if (Copy_Pin <= PIN7)
	{
		switch (Copy_Port)
		{
			case PORTA: Local_u8Value = GET_BIT(PINA_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;                                
			case PORTB: Local_u8Value = GET_BIT(PINB_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;                                
			case PORTC: Local_u8Value = GET_BIT(PINC_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;                                
			case PORTD: Local_u8Value = GET_BIT(PIND_REGISTER,Copy_Pin); /* return MDIO_DONE; */	break;
			default   : /* return MDIO_WRONG_PORT; */ 												break;
		}
	}
	else
	{
		/* return MDIO_WRONG_PIN; */ 
	}
	
	return Local_u8Value;
}


/* IO Ports */
void MDIO_voidSetPortDirection(MDIO_PORT_Type Copy_Port, u8 Copy_u8Direction)
{
	switch (Copy_Port)
	{
		case PORTA: DDRA_REGISTER = Copy_u8Direction; /* return MDIO_DONE; */	break;                    
		case PORTB: DDRB_REGISTER = Copy_u8Direction; /* return MDIO_DONE; */	break;                    
		case PORTC: DDRC_REGISTER = Copy_u8Direction; /* return MDIO_DONE; */	break;                    
		case PORTD: DDRD_REGISTER = Copy_u8Direction; /* return MDIO_DONE; */	break;
		default   : /* return MDIO_WRONG_PORT; */ 								break;
	}
}

void MDIO_voidSetPortValue(MDIO_PORT_Type Copy_Port, u8 Copy_u8Value)
{
	switch (Copy_Port)
	{
		case PORTA: PORTA_REGISTER = Copy_u8Value; /* return MDIO_DONE; */	break;                
		case PORTB: PORTB_REGISTER = Copy_u8Value; /* return MDIO_DONE; */	break;                
		case PORTC: PORTC_REGISTER = Copy_u8Value; /* return MDIO_DONE; */	break;                
		case PORTD: PORTD_REGISTER = Copy_u8Value; /* return MDIO_DONE; */	break;
		default   : /* return MDIO_WRONG_PORT; */ 							break;
	}
}

void MDIO_voidTogglePortValue(MDIO_PORT_Type Copy_Port)
{
	switch (Copy_Port)
	{
		case PORTA: TOG_8BIT(PORTA_REGISTER); /* return MDIO_DONE; */	break;
		case PORTB: TOG_8BIT(PORTB_REGISTER); /* return MDIO_DONE; */	break;                   
		case PORTC: TOG_8BIT(PORTC_REGISTER); /* return MDIO_DONE; */ 	break;                   
		case PORTD: TOG_8BIT(PORTD_REGISTER); /* return MDIO_DONE; */	break;
		default   : /* return MDIO_WRONG_PORT; */ 						break;
	}
}

u8   MDIO_u8GetPortValue(MDIO_PORT_Type Copy_Port)
{
	u8 Local_u8Value = MDIO_INITIAL_VALUE;
	
	switch (Copy_Port)
	{
		case PORTA: Local_u8Value = PINA_REGISTER; /* return MDIO_DONE; */	break;                          
		case PORTB: Local_u8Value = PINB_REGISTER; /* return MDIO_DONE; */ 	break;                          
		case PORTC: Local_u8Value = PINC_REGISTER; /* return MDIO_DONE; */ 	break;                          
		case PORTD: Local_u8Value = PIND_REGISTER; /* return MDIO_DONE; */  break;
		default   : /* return MDIO_WRONG_PORT; */ 							break;
	}
	
	return Local_u8Value;
}
/***************************************************************************************************************************************************/

/***************************************************************************************************************************************************/