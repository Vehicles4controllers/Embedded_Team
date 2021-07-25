//#include "STD_TYPES.h"
//#include "inc/tm4c123gh6pm.h"
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include "UART_int.h"
//#include "I2C_int.h"
//#include "IMU_priv.h"
//#include "STK_interface.h"
//#include "QMC5883_int.h"
//#include<math.h>
//
//  char sensordata[14];
//
//char msg[20];
//short heading;
//extern f32 initial;
//int main(void)
//{
//
//    UART_voidInit(UART0, 9600, 8, 1, NONE);
//    QMC5883_voidInit(I2C1);
//
//    while(1)
//    {
//
//        heading = QMC5883_f32GetHeading();
//        ltoa(heading, msg, 10);
//        UART_voidTransmitString(UART0, msg);
//        UART_voidTransmitChar(UART0, '\n');
//        strcpy(msg, "");
//     Delay(4);
//    }
//}










#include "STD_TYPES.h"
#include "GPIO_int.h"
#include <stdlib.h>
#include <string.h>
#include "UART_int.h"
#include "I2C_int.h"
#include "STK_interface.h"
#include "QMC5883_int.h"
#include "KalmanFilter_int.h"

  char sensordata[14];

char msg[20];
short heading;
void Blink_LED()
{
    static char x = 0;
    if(x)
    {
        GPIO_voidSetPin(PORTF, 1, HIGH);
    }
    else
    {
        GPIO_voidSetPin(PORTF, 1, LOW);
    }

    x = !x;

}
int main(void)
{
    GPIO_voidInitializeDigitalPin(PORTF, 1, OUTPUT, Drive_8mA);
    //MSTK_voidInit();
    UART_voidInit(UART0, 9600, 8, 1, NONE);
    QMC5883_voidInit(I2C1);
    IMU_voidMPU6050Init(I2C1);
    KalmanFilter_voidHeadingInit(0.004);
    //MSTK_voidCreateTask(2, 4,  Blink_LED);
    //MSTK_voidStartScheduler();
    while(1)
    {
        //KalmanFilter_voidGetReadings();
        heading = KalmanFilter_f32GetAngle();
        ltoa(heading, msg, 10);
        UART_voidTransmitString(UART0, msg);
//        UART_voidTransmitChar(UART0, ' ');
//        f32 newAngle = QMC5883_f32GetHeading();
//        ltoa(newAngle, msg, 10);
        UART_voidTransmitChar(UART0, '\n');
        strcpy(msg, "");
     Delay(4);
    }
}




