/*
 * I2C_prog.c
 *
 *  Created on: Nov 19, 2020
 *      Author: al-almia
 */
#include "I2C_int.h"
#include "RegisterMap.h"
#include"GPIO_int.h"
extern long int clockFrequency;

struct I2C_PORT
{
    gpio_port_t PORT;
    char pin1;
    char pin2;
};

struct I2C_PORT I2C_PINS[4] = {{PORTB,2,3},{PORTA,6,7},{PORTE,4,5},{PORTD,0,1}};

void I2C_voidConnectClock(I2C_t I2C)
{
    volatile long int* reg = 0x400FE620;
    *reg |= (1 << I2C);
}
void I2C_voidSetMode(I2C_t I2C, mode_t mode)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMCR;
    *reg |= (1 << mode);

}

void I2C_voidSetClockFrequency(I2C_t I2C, long int freq)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMTPR;
    *reg |= (clockFrequency/20*freq) - 1;

}
/*static*/ int I2C_intWaitTillDone(I2C_t I2C)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMCS;
    while((*reg) & 1);   /* wait until I2C master is not busy */
    return (*reg) & 0xE; /* return I2C error code, 0 if no error*/
}

char I2C_charWrite(I2C_t I2C, int slave_address, char slave_memory_address, char data)
{

    char error;

    /* send slave address and starting address */
    I2C_voidCallSlave(I2C, (slave_address << 1));
    I2C_voidSetDataRegister(I2C,slave_memory_address);
    I2C_voidSetCommunication(I2C, 3);                      /* S-(saddr+w)-ACK-maddr-ACK */

    error = I2C_intWaitTillDone(I2C);   /* wait until write is complete */
    if (error) return error;

    /* send data */
    I2C_voidSetDataRegister(I2C, data);
    I2C_voidSetCommunication(I2C, 5);                         /* -data-ACK-P */
    error = I2C_intWaitTillDone(I2C);       /* wait until write is complete */
    while((I2C_charReadFlagRegister(I2C)) & 0x40);             /* wait until bus is not busy */
    error = (I2C_charReadFlagRegister(I2C)) & 0xE;
    if (error) return error;

    return 0;       /* no error */
}
char I2C_charRead(I2C_t I2C, int slaveAddr, char slave_memory_address, int byteCount, char* data)
{
    char error;

   if (byteCount <= 0)
       return -1;         /* no read was performed */

   /* send slave address and starting address */
   I2C_voidCallSlave(I2C, (slaveAddr << 1));
   I2C_voidSetDataRegister(I2C,slave_memory_address);
   I2C_voidSetCommunication(I2C, 3);       /* S-(saddr+w)-ACK-maddr-ACK */
   error = I2C_intWaitTillDone(I2C);
   if (error)
       return error;

   /* to change bus from write to read, send restart with slave addr */
   I2C_voidCallSlave(I2C, ((slaveAddr << 1) + 1));   /* restart: -R-(saddr+r)-ACK */

   if (byteCount == 1)             /* if last byte, don't ack */
       I2C_voidSetCommunication(I2C, 7);              /* -data-NACK-P */
   else                            /* else ack */
       I2C_voidSetCommunication(I2C, 0xB);            /* -data-ACK- */
   error = I2C_intWaitTillDone(I2C);
   if (error) return error;

   *data++ = I2C_charReadDataRegister(I2C);            /* store the data received */

   if (--byteCount == 0)           /* if single byte read, done */
   {
       while((I2C_charReadFlagRegister(I2C)) & 0x40);    /* wait until bus is not busy */
       return 0;       /* no error */
   }

   /* read the rest of the bytes */
   while (byteCount > 1)
   {
       I2C_voidSetCommunication(I2C, 9);          /* -data-ACK- */
       error = I2C_intWaitTillDone(I2C);
       if (error) return error;
       byteCount--;
       *data++ = I2C_charReadDataRegister(I2C);       /* store data received */
   }

   I2C_voidSetCommunication(I2C, 5);                /* -data-NACK-P */
   error = I2C_intWaitTillDone(I2C);
   *data = I2C_charReadDataRegister(I2C);           /* store data received */
   while((I2C_charReadFlagRegister(I2C)) & 0x40);        /* wait until bus is not busy */

   return 0;       /* no error */
}

void I2C_voidInit(I2C_t I2C, mode_t mode, long int clock)
{
    I2C_voidConnectClock(I2C);
    GPIO_voidConnectClock(I2C_PINS[I2C].PORT);
    GPIO_voidSetBus(I2C_PINS[I2C].PORT, AHB);
    GPIO_voidEnableDigitalFunction(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin1);
    GPIO_voidEnableAlternateFunction(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin1);
    GPIO_voidEnableDigitalFunction(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin2);
    GPIO_voidEnableAlternateFunction(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin2);
    GPIO_voidPinMUltiplexerSet(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin1,3);
    GPIO_voidPinMUltiplexerSet(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin2,3);
    GPIO_voidSetOpenDrain(I2C_PINS[I2C].PORT,I2C_PINS[I2C].pin2);
    I2C_voidSetMode(I2C, mode);
    I2C_voidSetClockFrequency(I2C, clock);


}
void I2C_voidCallSlave(I2C_t I2C, long int slave_address)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMSA;
    *reg = slave_address;
}

void I2C_voidSetDataRegister(I2C_t I2C, char data)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMDR;
    *reg = data;

}

void I2C_voidSetCommunication(I2C_t I2C, char commMode)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMCS;
    *reg = commMode;
}
char I2C_charReadFlagRegister(I2C_t I2C)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMCS;
    return *reg;
}

char I2C_charReadDataRegister(I2C_t I2C)
{
    volatile long int* reg = I2C_BASE + (I2C << 12) + I2CMDR;
    return *reg;
}
