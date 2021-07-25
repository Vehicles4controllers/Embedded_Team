/*
 * KalmanFilter_config.h
 *
 *  Created on: Apr 11, 2021
 *      Author: LOGO CS
 */

#ifndef KALMANFILTER_CONFIG_H_
#define KALMANFILTER_CONFIG_H_

#include"STD_TYPES.h"

f32 P[2][2] = {{0.0, 0.0}, {0.0, 0.0}};
f32 R = 200;
f32 sigma1 = 0.001f, sigma2 = 0.003f;
f32 Corrected_Angle = 0.0f;
f32 Corrected_Rate = 0.0f;
f32 bias = 0.0f;

#endif /* KALMANFILTER_CONFIG_H_ */
