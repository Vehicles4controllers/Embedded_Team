/*
 * utils.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: 7
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SETBIT(Reg,bit)          Reg |= (1 << bit)
#define CLRBIT(Reg,bit)          Reg &= ~(1 << bit)
#define TOGGLEBIT(Reg,bit)       Reg ^= (1 << bit)

#endif /* UTILS_H_ */
