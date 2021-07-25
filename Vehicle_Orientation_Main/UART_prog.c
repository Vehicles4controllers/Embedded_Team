/*
 * UART_prog.c
 *
 *  Created on: Apr 28, 2020
 *      Author: AL-alamia
 */
#include "UART_int.h"
#include "GPIO_int.h"
#include "RegisterMap.h"
#include <string.h>
struct UART_PORT
{
    gpio_port_t PORT1;
    char pin1;
    gpio_port_t PORT2;
    char pin2;
};


extern long int clockFrequency;
float clockDivider = 16.0;
struct UART_PORT PINS[8] = {{PORTA,0,PORTA,1},{PORTB,0,PORTB,1},{PORTD,6,PORTD,7},{PORTC,6,PORTC,7},{PORTC,4,PORTC,5},{PORTE,4,PORTE,5},{PORTD,4,PORTD,5},{PORTE,0,PORTE,1}};

void UART_voidConnectClock(UART_t UART)
{
    volatile long int* reg = 0x400FE618;
    *reg |= (1 << UART);
}

void UART_voidDisable(UART_t UART)
{
    volatile long int* reg =  0x4000C030 + (UART*(1 << 12));
    *reg &= ~(1 << 0);

}
void UART_voidEnable(UART_t UART)
{
    volatile long int* reg =  0x4000C030 + (UART*(1 << 12));
    *reg |= 1;
    *reg |= (1 << 8)|(1 << 9);
}

void UART_voidSetWordLength(UART_t UART,char word)
{
    volatile long int* reg =  0x4000C02C + (UART*(1 << 12));
    *reg |= ((word-5)<<5);

}
void UART_voidSetStopBits(UART_t UART,char stopBits)
{
    volatile long int* reg =  0x4000C02C + (UART*(1 << 12));
    *reg |= ((stopBits - 1) << 3);
}
void UART_voidSetParity(UART_t UART,parity_t parity)
{
    volatile long int* reg =  0x4000C02C + (UART*(1 << 12));
    *reg |= parity;
}
void UART_voidSetBaudRate(UART_t UART,long int Baud)
{
    //float UARTBRFD = (((clockFrequency%(Baud * clockDivider))*64.0)/Baud) + 0.5;
    double BRD = (clockFrequency / clockDivider)/Baud;
    double UARTBRFD = ((BRD - (int)BRD)*64) + 0.5;
    volatile long int* reg =  0x4000C024 + (UART*(1 << 12));
    *reg |= (long int)((clockFrequency / clockDivider)/Baud);
    reg = 0x4000C028 + (UART*(1 << 12));
    *reg |= (int)UARTBRFD;
}
void UART_voidInit(UART_t UART,long int Baud,char word,char stop,parity_t parity)
{

    UART_voidConnectClock(UART);
   /* provide clock to UART0 */
   /* UART0 initialization */
    UART_voidDisable(UART);  /* disable UART0 */
    UART_voidSetBaudRate(UART,Baud);
    UART_voidSetWordLength(UART,word);
    UART_voidSetStopBits(UART,stop);
    UART_voidSetParity(UART,parity);
    UART_voidEnableFIFOs(UART);
    GPIO_voidConnectClock(PINS[UART].PORT1);
    GPIO_voidConnectClock(PINS[UART].PORT2);
    GPIO_voidSetBus(PINS[UART].PORT1,AHB);
    GPIO_voidEnableDigitalFunction(PINS[UART].PORT1,PINS[UART].pin1);
    GPIO_voidEnableAlternateFunction(PINS[UART].PORT1,PINS[UART].pin1);
    GPIO_voidSetBus(PINS[UART].PORT2,AHB);
    GPIO_voidEnableDigitalFunction(PINS[UART].PORT2,PINS[UART].pin2);
    GPIO_voidEnableAlternateFunction(PINS[UART].PORT2,PINS[UART].pin2);
    GPIO_voidPinMUltiplexerSet(PINS[UART].PORT1,PINS[UART].pin1,1);
    GPIO_voidPinMUltiplexerSet(PINS[UART].PORT2,PINS[UART].pin2,1);
    UART_voidEnable(UART);

}

void UART_voidEnableFIFOs(UART_t UART)
{
    volatile long int* reg =  0x4000C02C + (UART*(1 << 12));
    *reg |= (1 << 4);
}

void UART_voidDisableFIFOs(UART_t UART)
{
    volatile long int* reg =  0x4000C02C + (UART*(1 << 12));
    *reg &= ~(1 << 4);
}

void UART_voidTransmitChar(UART_t UART,char character)
{
    volatile long int* reg =  0x4000C000 + (UART*(1 << 12));
    while((*reg) & (1 << 5));
    reg =  0x4000C000 + (UART*(1 << 12));
    *reg |= character;
}
void UART_voidTransmitString(UART_t UART,char* msg)
{
    int i = 0;
    volatile long int* reg =  0x4000C018 + (UART*(1 << 12));
    for(i = 0 ; i < strlen(msg) ; i++)
    {
        UART_voidTransmitChar(UART, msg[i]);
    }
}

char UART_u8RecieveChar(UART_t UART)
{
    volatile long int* reg =  0x4000C018 + (UART*(1 << 12));
    while((*reg) & (1 << 4));
    reg =  0x4000C000 + (UART*(1 << 12));
    return *reg;
}

char* UART_u8RecieveString(UART_t UART)
{
    static char msg[10];
    int i = 0;
    for(i = 0 ; i < 10 ; i++)
    {
        msg[i] = UART_u8RecieveChar(UART);
        if(msg[i] == '/0')
        {
            break;
        }
    }
    return msg;
}
void UART_voidSetLoopBackMode(UART_t UART)
{
    volatile long int* reg =  0x4000C030 + (UART*(1 << 12));
    *reg |= (1 << 7);

}

