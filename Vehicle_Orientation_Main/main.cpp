
extern"C"
{
#include "STD_TYPES.h"
#include "GPIO_int.h"
#include <stdlib.h>
#include <string.h>
#include "UART_int.h"
#include "I2C_int.h"
#include "STK_interface.h"
#include "QMC5883_int.h"
#include "IMU_int.h"
}
#include<FilteredAngle.h>


char msg[20];
short heading;

int main(void)
{
    UART_voidInit(UART0, 9600, 8, 1, NONE);
    QMC5883_voidInit(I2C1);
    IMU_voidMPU6050Init(I2C1);

    FilteredAngle angleYaw = FilteredAngle(1, 0.004, QMC5883_f32GetHeading, IMU_u16GetGyroZ);
    FilteredAngle anglePitch = FilteredAngle(2, 0.004, IMU_u16GetPITCH_ACC, IMU_u16GetGyroY);
    FilteredAngle angleRoll = FilteredAngle(3, 0.004, IMU_u16GetROLL_ACC, IMU_u16GetGyroY);

    angleYaw.PushInStack();
    anglePitch.PushInStack();
    angleRoll.PushInStack();

    while(1)
    {
        heading = angleYaw.KalmanFilter_f32GetAngle();

        ltoa(heading, msg, 10);
        UART_voidTransmitString(UART0, msg);
        UART_voidTransmitChar(UART0, ' ');

        heading = anglePitch.KalmanFilter_f32GetAngle();

        ltoa(heading, msg, 10);
        UART_voidTransmitString(UART0, msg);
        UART_voidTransmitChar(UART0, ' ');

        heading = angleRoll.KalmanFilter_f32GetAngle();

        ltoa(heading, msg, 10);
        UART_voidTransmitString(UART0, msg);
        UART_voidTransmitChar(UART0, '\n');
        strcpy(msg, "");
     Delay(4);
    }
}



