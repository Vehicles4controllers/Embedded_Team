
#ifndef BIT_MATH_H
#define BIT_MATH_H

/* Bit Math for 1 bit */
#define SET_BIT(VAR,BITNO) 						(VAR) |=  (   1   << (BITNO))
#define CLR_BIT(VAR,BITNO) 						(VAR) &= ~(   1   << (BITNO))
#define TOG_BIT(VAR,BITNO) 						(VAR) ^=  (   1   << (BITNO))
#define GIV_BIT(VAR,GVAR,BITNO) 				(VAR) |=  ((GVAR) << (BITNO))
#define GET_BIT(VAR,BITNO) 						(((VAR) >> (BITNO)) & 0x01)

#endif
/***************************************************************************************************************************************************/
