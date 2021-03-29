/* Header Files Inclusions */
/* Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "DIO_interface.h" 		// DIO
#include <util/delay.h> 		// Instead of TIMER
/* HAL */
#include "SEVSEG_interface.h"	// 7-Segments

/* Configuration */
#define RED_LIGHT_PIN		PORTC,PIN0
#define YELLOW_LIGHT_PIN	PORTC,PIN1
#define GREEN_LIGHT_PIN		PORTC,PIN2
#define COUNTER_LEFT_PORT	PORTA
#define COUNTER_LEFT_COMMON	HSEVSEG_CATHODE
#define COUNTER_RIGHT_PORT	PORTB
#define COUNTER_LEFT_COMMON	HSEVSEG_CATHODE

/* Functions */
/* Set PINs/PORTs Direction */
void voidInit(void)
{
	MDIO_voidSetPinDirection(RED_LIGHT_PIN,OUTPUT);	// Red Light
	MDIO_voidSetPinDirection(YELLOW_LIGHT_PIN,OUTPUT);	// Yellow Light
	MDIO_voidSetPinDirection(GREEN_LIGHT_PIN,OUTPUT);	// Green Light
	MDIO_voidSetPortDirection(COUNTER_LEFT_PORT,OUTPUT_ALL);
	MDIO_voidSetPortDirection(COUNTER_RIGHT_PORT,OUTPUT_ALL);
}

/* Red Light Function */
void voidOnRedLight(void)
{
	MDIO_voidSetPinValue(RED_LIGHT_PIN,HIGH);
	MDIO_voidSetPinValue(YELLOW_LIGHT_PIN,LOW);
	MDIO_voidSetPinValue(GREEN_LIGHT_PIN,LOW);
}

/* Yellow Light Function */
void voidOnYellowLight(void)
{
	MDIO_voidSetPinValue(RED_LIGHT_PIN,LOW);
	MDIO_voidSetPinValue(YELLOW_LIGHT_PIN,HIGH);
	MDIO_voidSetPinValue(GREEN_LIGHT_PIN,LOW );
}

/* Green Light Function */
void voidOnGreenLight(void)
{
	MDIO_voidSetPinValue(RED_LIGHT_PIN,LOW);
	MDIO_voidSetPinValue(YELLOW_LIGHT_PIN,LOW);
	MDIO_voidSetPinValue(GREEN_LIGHT_PIN,HIGH);
}

/* Main */
void main(void)
{
	/* DIO Initialization */
	MDIO_voidInit();

	/* Set PINs/PORTs Direction */
	voidInit();

	/* Counter Variable */
	s8 Local_s8CounterLeft  = 0;
	s8 Local_s8CounterRight = 0;

	while(1)
	{
		voidOnRedLight();

		for (Local_s8CounterLeft=2;Local_s8CounterLeft>=0;Local_s8CounterLeft--)
		{
			HSEVSEG_voidDisplay(COUNTER_LEFT_PORT,COUNTER_LEFT_COMMON,Local_s8CounterLeft);
			for (Local_s8CounterRight=9;Local_s8CounterRight>=0;Local_s8CounterRight--)
			{
				HSEVSEG_voidDisplay(COUNTER_RIGHT_PORT,HSEVSEG_CATHODE,Local_s8CounterRight);
				_delay_ms(1000);
			}
		}

		voidOnGreenLight();

		for (Local_s8CounterLeft=5;Local_s8CounterLeft>=0;Local_s8CounterLeft--)
		{
			HSEVSEG_voidDisplay(COUNTER_LEFT_PORT,COUNTER_LEFT_COMMON,Local_s8CounterLeft);
			for (Local_s8CounterRight=9;Local_s8CounterRight>=0;Local_s8CounterRight--)
			{
				HSEVSEG_voidDisplay(COUNTER_RIGHT_PORT,COUNTER_LEFT_COMMON,Local_s8CounterRight);
				_delay_ms(1000);
				if ((Local_s8CounterLeft==0) && (Local_s8CounterRight==5))
				{
					voidOnYellowLight();
				}
			}
		}
	}
}
