/*
 * Timer_prog.c
 *
 *  Created on: Apr 19, 2020
 *      Author: AL-alamia
 */
#include"Timer_int.h"
#include"Interrupt_int.h"

extern long int clockFrequency;
extern void (*RAM_Vector[155])(void);

volatile long int Timers[10] = {0x40036000,0x40037000,0x4004C000,0x4004D000,0x4004E000,0x4004F000,0x40030000,0x40031000,0x40032000,0x40033000,0x40034000,0x40050000};
size_t currentSize=Normal;
void Timer_voidSetMode(timer_t timer,part_t part,mode_t mode)
{
    volatile long int* reg = Timers[timer+currentSize]+GPTMTnMR+(part/2);
    *reg |= mode;

}
void TImer_voidSetDirection(timer_t timer,part_t part,direction_t direction)
{
    volatile long int* reg = Timers[timer+currentSize]+GPTMTnMR+(part/2);
    *reg |= direction;
}

void Timer_voidSetSize(timer_t Timer,size_t size,char width)
{
    char width_mask = width/16;
    char size_mask = size/6;
    volatile long int* reg = Timers[Timer+size];
    currentSize = size;
    *reg |= ((width_mask | (size_mask << 1)) & 0x02)*2;
}
void Timer_voidEnableInterrupt(part_t part,interruptMode_t Interrupt)
{
    GPTMIMR |= (1 << (Interrupt+part-((part*Interrupt)/32)));
}
void Timer_voidDisableInterrupt(part_t part,interruptMode_t Interrupt)
{
    GPTMIMR &= ~(1 << (Interrupt+part-((part*Interrupt)/32)));
}
void Timer_voidConnectClock(timer_t Timer)
{
    RCGCTIMER |= (1 << Timer);
}
void Timer_voidEnable(timer_t Timer,part_t part)
{
    volatile long int* reg = Timers[Timer+currentSize]+GPTMCTL;
    *reg |= (1 << part);

}
void Timer_voidDisable(timer_t Timer,part_t part)
{
    volatile long int* reg = Timers[Timer+currentSize]+GPTMCTL;
    *reg &= ~(1 << part);

}

void Timer_voidLoad(timer_t Timer,part_t part,unsigned int val)
{
    if(part == A)
    {
        volatile long int* reg = Timers[Timer+currentSize]+GPTMTAILR;
        *reg = val;

    }
    else if(part == B)
    {
        volatile long int* reg = Timers[Timer+currentSize]+GPTMTBILR;
        *reg = val;

    }

}

void Timer_voidSetPrescaler(timer_t Timer,part_t part,unsigned char val)
{
    if(part == A)
    {
        volatile long int* reg = Timers[Timer+currentSize]+GPTMTAPR;
        *reg = val;

    }
    else if(part == B)
    {
        volatile long int* reg = Timers[Timer+currentSize]+GPTMTBPR;
        *reg = val;

    }

}


void Timer_voidEvery(timer_t Timer,double period,void* fn)
{
    Load_Vector_Table();
    double MAX_16 = (65536.0/clockFrequency) * 1000 * 256;
    double MAX_32 = (pow(2,32)/clockFrequency) * 1000;
    double MAX_64 = (pow(2,64)/clockFrequency) * 1000;

    Timer_voidConnectClock(Timer);
    Timer_voidDisable(Timer,A);
    Timer_voidDisable(Timer,B);
    if(period <= MAX_16)
    {
        Timer_voidSetPrescaler(Timer,A,255);
        double unitTime = 256000.0/clockFrequency;
        Timer_voidSetSize(Timer,Normal,16);
        Timer_voidLoad(Timer,A,(unsigned int)(period/unitTime));
        if(Timer == Timer0)
        {
            Interrupt_voidEnable(19);
            RAM_Vector[19] = fn;
        }
        Timer_voidEnableInterrupt(A,TimeOut);

    }
    else if(period <= MAX_32)
    {

    }
    Timer_voidSetMode(Timer,A,Periodic);

    Timer_voidEnable(Timer0,A);


}
