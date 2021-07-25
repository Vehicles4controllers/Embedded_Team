/*
 * QMC5883_int.h
 *
 *  Created on: Mar 22, 2021
 *      Author: LOGO CS
 */

#ifndef QMC5883_INT_H_
#define QMC5883_INT_H_

#include"STD_TYPES.h"
#include"I2C_int.h"

void QMC5883_voidSetAddress(u8);
void QMC5883_voidWriteRegister(u8, u8);
void QMC5883_voidInit(I2C_t);
void QMC5883_voidSetMode(u16, u16, u16, u16);
void QMC5883_voidSoftReset(void);

u16 QMC5883_u16Read(short*, short*, short*);
f32 QMC5883_f32GetAzimuth(pu16, pu16);

#endif /* QMC5883_INT_H_ */
