/*
 * Timer_int.h
 *
 *  Created on: Apr 19, 2020
 *      Author: AL-alamia
 */

#ifndef TIMER_INT_H_
#define TIMER_INT_H_

#define     GPTMCFG             0x40030000
#define     RCGCTIMER                        (*((volatile unsigned int*)0x400FE604))
#define     GPTMCTL             0x00C
#define     GPTMIMR                          (*((volatile unsigned int*)0x40030018))
#define     GPTMTnMR            0x004
#define     GPTMTAILR           0x028
#define     GPTMTBILR           0x02C
#define     GPTMTAPR            0x038
#define     GPTMTBPR            0x03C
#define GPTMICR                         (*((volatile unsigned int*)0x40030024))

typedef enum{Timer0 = 0,Timer1,Timer2,Timer3,Timer4,Timer5}timer_t;
typedef enum{Wide = 0,Normal=6}size_t;
typedef enum{TimeOut = 0,CaptureMatch,CaptureEvent,Match=4}interruptMode_t;
typedef enum{OneShot = 1,Periodic,Capture}mode_t;
typedef enum{A=0,B=8}part_t;
typedef enum{Enable=0,Stall,ADC,PWM}module_t;
typedef enum{UP=16,DOWN=0}direction_t;
void Timer_voidEnable(timer_t,part_t);
void Timer_voidDisable(timer_t,part_t);
void TImer_voidSetDirection(timer_t,part_t,direction_t);
void Timer_voidConnectClock(timer_t);
void Timer_voidSetSize(timer_t,size_t,char);
void Timer_voidSetMode(timer_t,part_t,mode_t);
//void Timer_voidStart(timer_t,module_t);
//void Timer_voidStop(timer_t,module_t);
void Timer_voidEnableInterrupt(part_t,interruptMode_t);
void Timer_voidDisableInterrupt(part_t,interruptMode_t);
void Timer_voidEvery(timer_t,double,void*);
void Timer_voidCountUP();
void Timer_voidLoad(timer_t,part_t,unsigned int);
void Timer_voidSetPrescaler(timer_t,part_t,unsigned char);
#endif /* TIMER_INT_H_ */
