/*
 * KalmanFilter_int.h
 *
 *  Created on: Apr 11, 2021
 *      Author: LOGO CS
 */

#ifndef KALMANFILTER_INT_H_
#define KALMANFILTER_INT_H_

#include"STD_TYPES.h"


void KalmanFilter_voidHeadingInit(f32 deltaT);
f32 KalmanFilter_f32GetPredictedState(f32 newAngle, f32 newRate);
f32 KalmanFilter_f32CalculateInnovation(void);
f32* KalmanFilter_f32CalculateKalmanGain(void);

f32 KalmanFilter_f32GetAngle(void);

void KalmanFilter_voidUpdateAngle(f32 newAngle, f32 newRate);
void KalmanFilter_voidGetReadings();
#endif /* KALMANFILTER_INT_H_ */
