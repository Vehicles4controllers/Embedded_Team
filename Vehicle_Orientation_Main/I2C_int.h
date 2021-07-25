/*
 * I2C_int.h
 *
 *  Created on: Nov 19, 2020
 *      Author: al-almia
 */

#ifndef I2C_INT_H_
#define I2C_INT_H_

typedef enum{I2C0 = 0, I2C1, I2C2, I2C3}I2C_t;
typedef enum{MASTER = 4, SLAVE = 0, LOOPBACK = 5}mode_t;
void I2C_voidConnectClock(I2C_t);

void I2C_voidSetMode(I2C_t, mode_t);


void I2C_voidSetClockFrequency(I2C_t, long int);
char I2C_charWrite(I2C_t, int, char, char);
char I2C_charRead(I2C_t, int, char, int, char*);

/*static*/ int I2C_intWaitTillDone(I2C_t);

void I2C_voidInit(I2C_t,mode_t ,long int);

void I2C_voidCallSlave(I2C_t, long int);

void I2C_voidSetDataRegister(I2C_t, char);

void I2C_voidSetCommunication(I2C_t, char);

char I2C_charReadFlagRegister(I2C_t);

char I2C_charReadDataRegister(I2C_t);

#endif /* I2C_INT_H_ */
