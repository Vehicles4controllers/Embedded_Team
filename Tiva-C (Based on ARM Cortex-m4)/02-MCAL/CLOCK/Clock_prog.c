/*
 * Clock_prog.c
 *
 *  Created on: May 6, 2020
 *      Author: AL-alamia
 */
#include "CLOCKDRIVER.h"
#include <math.h>
#include "RegisterMap.h"
long int clockFrequency = 16000000.0;
void Clock_voidFrequencySet(double Freq)
{

        char SYSDIV = ceil((400/Freq) - 1);
        // 0) Use RCC2

        RCC2 |=  0x80000000;  // USERCC2

        // 1) bypass PLL while initializing

        RCC2 |=  0x00000800;  // BYPASS2, PLL bypass

        // 2) select the crystal value and oscillator source

        RCC = (RCC &~0x000007C0)   // clear XTAL field, bits 10-6

                       + 0x00000540;   // 10101, configure for 16 MHz crystal

        RCC2 &= ~0x00000070;  // configure for main oscillator source

        // 3) activate PLL by clearing PWRDN

        RCC2 &= ~0x00002000;

        // 4) set the desired system divider

        RCC2 |= 0x40000000;   // use 400 MHz PLL

        RCC2 = (RCC2 &~ 0x1FC00000)  // clear system clock divider

                        + (SYSDIV<<22);      // configure for 80 MHz clock

        // 5) wait for the PLL to lock by polling PLLLRIS

        while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit

        // 6) enable use of PLL by clearing BYPASS

        RCC2 &= ~0x00000800;
        clockFrequency = (400/(SYSDIV + 1)) * 1000000;

    }



