/*
 * Delay.c
 *
 *  Created on: Jul 14, 2021
 *      Author: LOGO CS
 */
#include "Delay_int.h"

void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter*10000; i++);
}
