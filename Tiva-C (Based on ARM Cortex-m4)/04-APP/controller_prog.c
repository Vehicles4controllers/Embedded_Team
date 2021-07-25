/*
 * controller_prog.c
 *
 *  Created on: Jul 14, 2021
 *      Author: LOGO CS
 */
#include "GPIO_int.h"
#include "controller_int.h"
#include "controller_config.h"
#include "controller_priv.h"
#include "STD_TYPES.h"
#include "Delay_int.h"
speed_t current_speed = LOW;

void controller_voidInit(void)
{
    GPIO_voidInitializeDigitalPin(CONTROLLER_PORT, FORWARD, OUTPUT, Drive_8mA);
    GPIO_voidInitializeDigitalPin(CONTROLLER_PORT, BACKWARD, OUTPUT, Drive_8mA);
    GPIO_voidInitializeDigitalPin(CONTROLLER_PORT, RIGHT, OUTPUT, Drive_8mA);
    GPIO_voidInitializeDigitalPin(CONTROLLER_PORT, LEFT, OUTPUT, Drive_8mA);
    GPIO_voidInitializeDigitalPin(CONTROLLER_PORT, BRAKE, OUTPUT, Drive_8mA);
    GPIO_voidInitializeDigitalPin(CONTROLLER_PORT, ADJUST, OUTPUT, Drive_8mA);
}

void controller_voidForward(u16 distance)
{
    if(distance == FOREVER)
    {
        GPIO_voidSetPin(CONTROLLER_PORT, BACKWARD, HIGH);
        GPIO_voidSetPin(CONTROLLER_PORT, BRAKE, HIGH);
        GPIO_voidSetPin(CONTROLLER_PORT, FORWARD, LOW);
    }
    else
    {

    }
}
void controller_voidBackward(u16 distance)
{
    if(distance == FOREVER)
    {
        GPIO_voidSetPin(CONTROLLER_PORT, FORWARD, HIGH);
        GPIO_voidSetPin(CONTROLLER_PORT, BRAKE, HIGH);
        GPIO_voidSetPin(CONTROLLER_PORT, BACKWARD, LOW);
    }
    else
    {

    }
}
void controller_voidRight(u16);
void controller_voidLeft(u16);
void controller_voidBrake(void)
{
    GPIO_voidSetPin(CONTROLLER_PORT, BRAKE, LOW);
}
void controller_voidAdjust(speed_t speed)
{
    switch(current_speed)
    {
    case MIN:
        if((speed == MEDIUM) || (speed == ACCELERATE))
        {
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
        }
        else if(speed == MAX)
        {
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
            Delay(20);
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, HIGH);
            Delay(20);
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
        }
        break;
    case MEDIUM:
        if((speed == MAX) || (speed == ACCELERATE))
        {
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
        }
        else if((speed == MIN) || (speed == DECELERATE))
        {
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
            Delay(20);
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, HIGH);
            Delay(20);
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
        }
        break;
    case MAX:
        if(speed == MIN)
        {
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
        }
        else if((speed == MEDIUM) || (speed == DECELERATE))
        {
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
            Delay(20);
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, HIGH);
            Delay(20);
            GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, LOW);
        }
        break;

    default:
        break;
    }
    current_speed = speed;
    Delay(20);
    GPIO_voidSetPin(CONTROLLER_PORT, ADJUST, HIGH);
}

