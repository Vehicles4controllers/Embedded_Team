/*
 * KalmanFilter_prog.c
 *
 *  Created on: Apr 18, 2021
 *      Author: LOGO CS
 */
#include"STD_TYPES.h"
#include"KalmanFilter_int.h"
#include"KalmanFilter_config.h"
#include "STK_interface.h"
#include"IMU_int.h"
#include"QMC5883_int.h"
#include "UART_int.h"

f32 deltaT;
static f32 corrected_angle = 0.0;

void KalmanFilter_voidHeadingInit(f32 delta_T)
{
    deltaT = delta_T;
    MSTK_voidInit();
    MSTK_voidCreateTask(1, delta_T * 1000.0,  KalmanFilter_voidGetReadings);
    MSTK_voidStartScheduler();
}

void KalmanFilter_voidGetReadings()
{
    f32 newAngle = QMC5883_f32GetHeading();
    f32 newRate = IMU_u16GetGyroZ();
    KalmanFilter_voidUpdateAngle(newAngle, newRate);
}

f32 KalmanFilter_f32GetPredictedState(f32 newAngle, f32 newRate)
{
    f32 corrected_rate = newRate - bias;
    newAngle += corrected_rate *135.0/(100000.0);

    P[0][0] += deltaT * (deltaT * P[1][1] - P[0][1] - P[1][0] + sigma1);
    P[0][1] -= deltaT * P[1][1];
    P[1][0] -= deltaT * P[1][1];
    P[1][1] += sigma2 * deltaT;

    return newAngle;
}
f32 KalmanFilter_f32CalculateInnovation(void)
{
    f32 S = P[0][0] + R;
    return S;
}
f32* KalmanFilter_f32CalculateKalmanGain(void)
{
    f32 S = KalmanFilter_f32CalculateInnovation();

    static f32 K[2];
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;
    return K;
}

void KalmanFilter_voidUpdateAngle(f32 newAngle, f32 newRate)
{
    corrected_angle = KalmanFilter_f32GetPredictedState(corrected_angle, newRate);

    f32* K = KalmanFilter_f32CalculateKalmanGain();

    f32 y = newAngle - corrected_angle; // Angle difference

    corrected_angle += K[0] * y;
    bias += K[1] * y;

    f32 P00_temp = P[0][0];
    f32 P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;


}

f32 KalmanFilter_f32GetAngle(void)
{
    return corrected_angle;
}
