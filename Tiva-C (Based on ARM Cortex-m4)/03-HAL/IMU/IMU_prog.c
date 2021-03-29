/*
 * IMU_prog.c
 *
 *  Created on: Jan 15, 2021
 *      Author: K I N G
 */



#include "I2C_int.h"
#include "IMU_int.h"
#include "IMU_priv.h"
#include "STK_interface.h"
#include "UART_int.h"

static I2C_t I2CBUS = I2C3;

static char sensordata[14];


static short gyro_x_cal = 0;
static short gyro_y_cal = 0;
static short gyro_z_cal = 0;


static short YAW = 0;
static short PITCH = 0;
static short ROLL = 0;



void IMU_voidMPU6050Init(I2C_t I2C)
{
    char commands[6] = {0x07, 0x01, 0x00, 0x00, 0x18, 0x01};
    I2CBUS = I2C;
    I2C_voidInit(I2C, MASTER, 100000);
    I2C_charWrite(I2C,0x68,SMPLRT_DIV, 0x07);
    I2C_charWrite(I2C,0x68,PWR_MGMT_1,  0x01);
    I2C_charWrite(I2C,0x68,CONFIG, 0x00);
    I2C_charWrite(I2C,0x68,ACCEL_CONFIG,0x00);
    I2C_charWrite(I2C,0x68,GYRO_CONFIG,0x18);
    I2C_charWrite(I2C,0x68,INT_ENABLE, 0x01);
    UART_voidInit(UART0, 9600, 8, 1, NONE);

}

void IMU_CalculateAngle(void)
{
    short GyroX = IMU_u16GetGyroZ();
    short GyroY = IMU_u16GetGyroZ();
    short GyroZ = IMU_u16GetGyroZ();

    static float angleYAW = 0;
    static float anglePITCH = 0;
    static float angleROLL = 0;

    angleYAW += GyroZ*135.0/(400000.0);
    anglePITCH += GyroZ*135.0/(400000.0);
    angleROLL += GyroZ*135.0/(400000.0);

    YAW = (short) angleYAW;
    PITCH = (short) anglePITCH;
    ROLL = (short) angleROLL;
}
void IMU_Gyro_Calibrate(void){
    int cal_int;
    short gyro_x = 0;
    short gyro_y = 0;
    short gyro_z = 0;

    for (cal_int = 0; cal_int < 2000 ; cal_int ++){
              I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
              gyro_x = (short) ( (sensordata[8] << 8 ) |sensordata[9] );
              gyro_y = (short) ( (sensordata[10] << 8 ) |sensordata[11] );
              gyro_z = (short) ( (sensordata[12] << 8 ) |sensordata[13] );
              gyro_x_cal += gyro_x;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
              gyro_y_cal += gyro_y;
              gyro_z_cal += gyro_z;
              Delay(3);                                                          //Delay 3us to simulate the 250Hz program loop
            }
                gyro_x_cal /= 2000;                                          //Divide the gyro_y_cal variable by 2000 to get the avarage offset
                gyro_y_cal /= 2000;
                gyro_z_cal /= 2000;


                MSTK_voidInit();
                MSTK_voidCreateTask(0, 1, IMU_CalculateAngle);
                MSTK_voidStartScheduler();




}

short IMU_u16GetGyroZ(void)
{



     I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
     short GyroZ = (short) ( (sensordata[12] << 8 ) |sensordata[13] );
     GyroZ -= gyro_z_cal;
     return GyroZ;

}
short IMU_u16GetGyroY(void)
{

     I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
     short GyroY = (short) ( (sensordata[10] << 8 ) |sensordata[11] );
     GyroY -= gyro_y_cal;
     return GyroY;

}
short IMU_u16GetGyroX(void)
{

     I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
     short GyroX = (short) ( (sensordata[8] << 8 ) |sensordata[9] );
     GyroX -= gyro_x_cal;
     return GyroX;

}


float IMU_u16GetTemperature(void)
{


    short Temperature;
     float Temp;
     I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
     Temperature = (short) ( (sensordata[6] << 8 ) |sensordata[7] );
     Temp = ((float)Temperature/340.00)+36.53;
     return Temp;

}


short IMU_u16GetACCZ(void)
{
    short accZ;
    I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
    accZ = (int) ( (sensordata[4] << 8 ) |sensordata[5] );
    return accZ;
}
short IMU_u16GetACCY(void)
{
    short accY;
    I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
    accY = (short) ( (sensordata[2] << 8 ) |sensordata[3] );
    return accY;
}
short IMU_u16GetACCX(void)
{
    short accX;
    I2C_charRead(I2CBUS, 0x68, ACCEL_XOUT_H, 14, sensordata);
    accX = (short) ( (sensordata[0] << 8 ) |sensordata[1] );
    return accX;
}

short IMU_u16GetYAW(void)
{

    return YAW;
}
short IMU_u16GetPITCH(void)
{

    return PITCH;
}
short IMU_u16GetROLL(void)
{

    return ROLL;
}


void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter*10000; i++);
}

