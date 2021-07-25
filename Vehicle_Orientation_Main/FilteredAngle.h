/*
 * FilteredAngle.h
 *
 *  Created on: Jun 6, 2021
 *      Author: LOGO CS
 */

#ifndef FILTEREDANGLE_H_
#define FILTEREDANGLE_H_

extern "C"
{
#include "STD_TYPES.h"
#include "STK_interface.h"
}

class FilteredAngle
{
private:

    f32 P[2][2] = {{0.0, 0.0}, {0.0, 0.0}};
    f32 R = 200;
    f32 sigma1 = 0.001f, sigma2 = 0.003f;
    f32 Corrected_Angle = 0.0f;
    f32 Corrected_Rate = 0.0f;
    f32 bias = 0.0f;
    f32 deltaT;
    u8 ID;

    f32(*MeasuringSensor_function)();
    short(*PredictionSensor_function)();

    static void KalmanFilter_voidGetReadings()
    {


        u8 ID = MSTK_voidGetLastCalled();
        extern FilteredAngle All_Angles[3];

        f32 newAngle = All_Angles[ID - 1].MeasuringSensor_function();
        f32 newRate = All_Angles[ID - 1].PredictionSensor_function();
        All_Angles[ID - 1].KalmanFilter_voidUpdateAngle(newAngle, newRate);


    }
    void KalmanFilter_voidUpdateAngle(f32 newAngle, f32 newRate)
    {


        this->Corrected_Angle = KalmanFilter_f32GetPredictedState(this->Corrected_Angle, newRate);
        f32* K = KalmanFilter_f32CalculateKalmanGain();

        f32 y = newAngle - this->Corrected_Angle; // Angle difference

        this->Corrected_Angle += K[0] * y;
        this->bias += K[1] * y;


        f32 P00_temp = this->P[0][0];
        f32 P01_temp = this->P[0][1];

        this->P[0][0] -= K[0] * P00_temp;
        this->P[0][1] -= K[0] * P01_temp;
        this->P[1][0] -= K[1] * P00_temp;
        this->P[1][1] -= K[1] * P01_temp;
    }
    f32 KalmanFilter_f32GetPredictedState(f32 newAngle, f32 newRate)
    {
        f32 corrected_rate = newRate - this->bias;
        newAngle += corrected_rate * 0.3 * this->deltaT;

        this->P[0][0] += this->deltaT * (this->deltaT * this->P[1][1] - this->P[0][1] - this->P[1][0] + this->sigma1);
        this->P[0][1] -= this->deltaT * this->P[1][1];
        this->P[1][0] -= this->deltaT * this->P[1][1];
        this->P[1][1] += this->sigma2 * this->deltaT;

        return newAngle;
    }
    f32 KalmanFilter_f32CalculateInnovation(void)
    {
        f32 S = this->P[0][0] + this->R;
        return S;
    }
    f32* KalmanFilter_f32CalculateKalmanGain(void)
    {
        f32 S = this->KalmanFilter_f32CalculateInnovation();

        static f32 K[2];
        K[0] = this->P[0][0] / S;
        K[1] = this->P[1][0] / S;
        return K;
    }
public:

    FilteredAngle(u16 angle_ID, f32 delta_t, f32(*Sensor_function)(), short(*Predictor_function)())
    {
        // TODO Auto-generated constructor stub
        this->ID = angle_ID;
        this->deltaT = delta_t;
        MSTK_voidInit();
        MSTK_voidCreateTask(angle_ID, delta_t * 1000, KalmanFilter_voidGetReadings);
        MSTK_voidStartScheduler();

        this->MeasuringSensor_function = Sensor_function;
        this->PredictionSensor_function = Predictor_function;

    }
    void PushInStack()
    {
        extern u8 stackPtr;
        extern FilteredAngle All_Angles[3];
        All_Angles[stackPtr] = *this;
        stackPtr++;
    }
    f32 KalmanFilter_f32GetAngle(void)
    {
        extern FilteredAngle All_Angles[3];
        return All_Angles[(this->ID) - 1].Corrected_Angle;
    }
    FilteredAngle()
    {

    }
    virtual ~FilteredAngle()
    {

    }
};




#endif /* FILTEREDANGLE_H_ */
