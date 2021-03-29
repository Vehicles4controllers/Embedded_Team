/*
 * Interrupt_int.h
 *
 *  Created on: Apr 9, 2020
 *      Author: AL-alamia
 */

#ifndef INTERRUPT_INT_H_
#define INTERRUPT_INT_H_

void Load_Vector_Table(void);
void Interrupt_voidEnable(unsigned char);
void Interrupt_voidDisable(unsigned char);
void Interrupt_voidSetPending(unsigned char);
void Interrupt_voidClearPending(unsigned char);
unsigned char Interrupt_voidGetPending(unsigned char);
void Interrupt_voidSetActive(unsigned char);
unsigned char Interrupt_voidGetState(unsigned char);
#endif /* INTERRUPT_INT_H_ */
