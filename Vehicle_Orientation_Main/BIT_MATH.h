/***************************************************************************************************************************************************/
/*                                                                 Bit Math Library                                                                */
/* File Name : BIT_MATH.h                                                                                                                          */
/* Aurthor   : Mahmoud Mohamed Kamal                                                                                                               */
/* Date      : 29 JUL 2020                                                                                                                         */
/* Version   : 1.0.0                                                                                                                               */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]                                                                                                  */
/* Layer     : LIB                                                                                                                                 */
/***************************************************************************************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

/* Bit Math for 1 bit */
#define SET_BIT(VAR,BITNO)                      (VAR) |=  (   1   << (BITNO))
#define CLR_BIT(VAR,BITNO)                      (VAR) &= ~(   1   << (BITNO))
#define TOG_BIT(VAR,BITNO)                      (VAR) ^=  (   1   << (BITNO))
#define GIV_BIT(VAR,GVAR,BITNO)                 (VAR) |=  ((GVAR) << (BITNO))
#define GET_BIT(VAR,BITNO)                      (((VAR) >> (BITNO)) & 0x01)

#endif
/***************************************************************************************************************************************************/
