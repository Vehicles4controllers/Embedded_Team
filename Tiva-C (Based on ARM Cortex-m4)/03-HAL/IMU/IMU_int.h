/*
 * IMU_interface.h
 *
 *  Created on: Jan 15, 2021
 *      Author: K I N G
 */

#ifndef IMU_INT_H_
#define IMU_INT_H_



void IMU_voidMPU6050Init(I2C_t);
void IMU_Gyro_Calibrate(void);

short IMU_u16GetGyroZ(void);
short IMU_u16GetGyroY(void);
short IMU_u16GetGyroX(void);

short IMU_u16GetACCZ(void);
short IMU_u16GetACCY(void);
short IMU_u16GetACCX(void);

short IMU_u16GetYAW(void);
short IMU_u16GetPITCH(void);
short IMU_u16GetROLL(void);


void IMU_CalculateAngle(void);
void Delay(unsigned long counter);


#endif /* IMU_INT_H_ */
