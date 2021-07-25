/*
 * controller_int.h
 *
 *  Created on: Jul 14, 2021
 *      Author: LOGO CS
 */

#ifndef CONTROLLER_INT_H_
#define CONTROLLER_INT_H_

#include "STD_TYPES.h"
#include "controller_priv.h"

void controller_voidInit(void);
void controller_voidForward(u16);
void controller_voidBackward(u16);
void controller_voidRight(u16);
void controller_voidLeft(u16);
void controller_voidBrake(void);
void controller_voidAdjust(speed_t);


#endif /* CONTROLLER_INT_H_ */
