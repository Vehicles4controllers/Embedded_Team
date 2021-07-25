/*
 * CLK_RegisterMap.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: 7
 */

#ifndef REGISTERMAP_H_
#define REGISTERMAP_H_

//System Control Registers
#define RCC               (*((volatile unsigned int *)0x400FE060))
#define RCC2              (*((volatile unsigned int *)0x400FE070))
#define MOSCCTL           (*((volatile unsigned int *)0x400FE07C))
#define PIOSCCAL          (*((volatile unsigned int *)0x400FE150))
#define PLLSTAT           (*((volatile unsigned int *)0x400FE168))
#define RCGCGPIO          (*((volatile unsigned int *)0x400FE608))
#define GPIOHBCTL         (*((volatile unsigned int *)0x400FE06C))
#define SYSCTL_RIS_R      (*((volatile unsigned int *)0x400FE050))

//GPIO Registers
#define PORT_DATA                0x3FC
#define PORT_DIR                 0x400
#define PORT_AFSEL               0x420
#define PORT_DEN                 0x51C
#define PORT_DRR                 0x500
//#define PORT_LOCK
#define GPIOPUR                  0x510
#define GPIOPDN                  0x514
#define GPIOCR                   0x524
#define GPIO_IM                  0x410
#define GPIOPCTL                 0x52C
#define GPIOICR                  0x41C


//I2C Registers
#define I2C_BASE        0x40020000
#define RCGCI2C         (*((volatile unsigned int *)0x400FE620))
#define I2CMCR0         (*((volatile unsigned int *)0x40020020))
#define I2CMTPR0         (*((volatile unsigned int *)0x4002000C))
#define I2CMSA0         (*((volatile unsigned int *)0x40020000))
#define I2CMDR0         (*((volatile unsigned int *)0x40020008))
#define I2CSOAR0         (*((volatile unsigned int *)0x40020800))
#define I2CMCS0         (*((volatile unsigned int *)0x40020004))
#define I2CSDR0         (*((volatile unsigned int *)0x40020808))

#define I2CMCR          0x020
#define I2CMTPR         0x00C
#define I2CMCS          0x004
#define I2CMDR          0x008
#define I2CMSA          0x000




#endif /* REGISTERMAP_H_ */
