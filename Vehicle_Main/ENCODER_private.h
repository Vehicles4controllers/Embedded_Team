/***************************************************************************************************************************************************/
/*                                                              Wheel Encoder Driver                                                               */
/* File Name : ENCODER_private.c 																    											   */
/* Aurthor   : Embedded Team																 	    											   */
/* Version	 : 1.0.0																		 	    											   */
/* Date      : 21 FEB 2021 																	 	    											   */
/* MC        : Tiva™ TM4C123GH6PM [ARM Cortex-m4]													  											   */
/* Layer     : HAL				 																	    										   */
/***************************************************************************************************************************************************/
#ifndef ENCODER_PRIVATE_H
#define ENCODER_PRIVATE_H

/***************************************************************************************************************************************************/  
/*                                                                     Private															       	   */
/***************************************************************************************************************************************************/ 
/* 1 meter = 612 */
#define HENCODER_CALIBRATION_VALUE 		612

/* PORTS */
#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3
#define PORTE   4
#define PORTF   5

/* Interrupt Number */
#if HENCODER_A_PHASE_PORT == PORTA
    #define HENCODER_INT_ENABLE 0
#elif HENCODER_A_PHASE_PORT == PORTB
    #define HENCODER_INT_ENABLE 1
#elif HENCODER_A_PHASE_PORT == PORTC
    #define HENCODER_INT_ENABLE 2
#elif HENCODER_A_PHASE_PORT == PORTD
    #define HENCODER_INT_ENABLE 3
#elif HENCODER_A_PHASE_PORT == PORTE
    #define HENCODER_INT_ENABLE 4
#elif HENCODER_A_PHASE_PORT == PORTF
    #define HENCODER_INT_ENABLE 30
#else
    #error("You Enter A Wrong HENCODER_A_PHASE_PORT")
#endif
/***************************************************************************************************************************************************/

#endif
/***************************************************************************************************************************************************/ 
