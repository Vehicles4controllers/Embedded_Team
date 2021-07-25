/*
 * UART_int.h
 *
 *  Created on: Apr 22, 2020
 *      Author: AL-alamia
 */

#ifndef UART_INT_H_
#define UART_INT_H_

typedef enum{UART0 = 0,UART1,UART2,UART3,UART4,UART5,UART6,UART7}UART_t;
typedef enum{NONE = 0,EVEN = 6,ODD = 2,STICK0 = 134,STICK1 = 130}parity_t;

void UART_voidConnectClock(UART_t);
void UART_voidDisable(UART_t);
void UART_voidEnable(UART_t);
void UART_voidSetWordLength(UART_t,char);
void UART_voidSetParity(UART_t,parity_t);
void UART_voidSetStopBits(UART_t,char);
void UART_voidSetBaudRate(UART_t,long int);
void UART_voidInit(UART_t,long int,char,char,parity_t);
void UART_voidEnableFIFOs(UART_t);
void UART_voidDisableFIFOs(UART_t);
void UART_voidSetLoopBackMode(UART_t);

void UART_voidTransmitChar(UART_t,char);
void UART_voidTransmitString(UART_t,char*);

char UART_u8RecieveChar(UART_t);
char* UART_u8RecieveString(UART_t);

#endif /* UART_INT_H_ */
