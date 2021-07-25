/* Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"RegisterMap.h"
#include"CLOCKDRIVER.h"
#include"GPIO_int.h"
#include"UART_interface.h"
#include"Interrupt_int.h"
#include"ENCODER_interface.h"
#include <string.h>


void MUART_voidWriteNum16Bit(MUART_CH_Type Copy_UARTChannel, u16 Copy_u16Num)
{
    u8  Local_u8DigitNum = 0;
    u16 Local_u16Num     = Copy_u16Num;
    u8  Local_u8Counter  = 0;
    u8 y =0;
    u8 Local_arru8Num[50] = {0};
    if (!Copy_u16Num)
    {
        Local_u8DigitNum = 1;
    }
    else
    {
        while (Local_u16Num)
        {
            Local_u16Num /= 10;
            ++Local_u8DigitNum;
        }
    }

    for (Local_u8Counter=Local_u8DigitNum; Local_u8Counter>0; Local_u8Counter--)
    {
        Local_u16Num = Copy_u16Num%10;
        Local_arru8Num[Local_u8Counter-1] = Local_u16Num;
        Copy_u16Num = Copy_u16Num/10;
    }

    for (Local_u8Counter=0; Local_u8Counter<Local_u8DigitNum; Local_u8Counter++)
    {

        y = Local_arru8Num[Local_u8Counter]+'0';
        MUART_voidSendDataSynch(Copy_UARTChannel, &(y));
    }
}
u8 Laststate;
s16 counter = 0;


int main(void)
{
    /* Initialization the UART */
    MUART_voidInit();
    /* Initialization the Wheel Encoder */
    HENCODER_voidInit();

    /* Controller */
    GPIO_voidInitializeDigitalPin(PORTA,5,OUTPUT,Drive_8mA); // Forward
    GPIO_voidSetPin(PORTA, 5, HIGH);
    setISR_PORTF(HENCODER_voidOperationISR);

    while(1)
    {

        MUART_voidSendDataSynch(UART5, "State:, Stop\r\n");
        MUART_voidSendDataSynch(UART5, "\r\n");

        /* Reset with Control */
        if (GPIO_u8ReadPin(PORTA, 5) == LOW)
        {
             /* Car Moving */
        }
        else
        {
            /* Car Stopped */
       //     HENCODER_voidResetCounter();
        }

    }
}
