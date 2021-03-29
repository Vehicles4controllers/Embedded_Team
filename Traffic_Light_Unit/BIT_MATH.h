/***************************************************************************************************************************************************/
/*										 	                       Bit Math Library										 	                       */
/* File Name : BIT_MATH.h 																				 	  									   */
/* Aurthor   : Mahmoud Mohamed Kamal																	 	  									   */
/* Date      : 29 JUL 2020 																				 	  									   */
/* Version	 : 1.1.0																					 	  									   */
/* MC        : ATmega32 [AVR]																 	    											   */
/* Layer     : LIB				 																												   */
/***************************************************************************************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

/* Bit Math for 1 bit */
#define SET_BIT(VAR,BITNO) 						(VAR) |=  (   1   << (BITNO))
#define CLR_BIT(VAR,BITNO) 						(VAR) &= ~(   1   << (BITNO))
#define TOG_BIT(VAR,BITNO) 						(VAR) ^=  (   1   << (BITNO))
#define GIV_BIT(VAR,VAL,BITNO) 					(VAR) |=  ( (VAL) << (BITNO))
#define EQU_BIT(VAR,VAL)	 					(VAR) |=  VAL
#define GET_BIT(VAR,BITNO) 						(((VAR) >> (BITNO)) & 0x01)

/* Bit Math for 3 bit */
#define CLR_3BIT(VAR,BITNO) 					(VAR) &= ~((0b111) << (BITNO))

/* Bit Math for 5 bit */
#define CLR_5BIT(VAR,BITNO) 					(VAR) &= ~((0b11111) << (BITNO))

/* Bit Math for 8 bit */
#define TOG_8BIT(VAR) 							(VAR) ^= 0xFF

/* Concatenate */
/* Note: It can Conc more than 8-bit but it takes only 8 Numbers, Parameters can more than 1 digit (0 or 00 or 101) */
#define CONC(X7,X6,X5,X4,X3,X2,X1,X0) 			CONC_HELPER(X7,X6,X5,X4,X3,X2,X1,X0)
#define CONC_HELPER(X7,X6,X5,X4,X3,X2,X1,X0)	0b##X7##X6##X5##X4##X3##X2##X1##X0

#endif
/***************************************************************************************************************************************************/
