/*
 * QMC5883_prog.c
 *
 *  Created on: Mar 22, 2021
 *      Author: LOGO CS
 */
#include<math.h>
#include"QMC5883_int.h"
#include"QMC5883_priv.h"
#include"I2C_int.h"
#include"STD_TYPES.h"

#define PI 3.14

static u8 address = QMC5883_ADDR;
static I2C_t I2CBUS = I2C0;

f32 initial;

void QMC5883_voidSetAddress(u8 addr)
{
    address = addr;
}

void QMC5883_voidInit(I2C_t I2C)
{
    I2CBUS = I2C;
    I2C_voidInit(I2C, MASTER, 100000);
    QMC5883_voidWriteRegister(0x0B,0x01);
    QMC5883_voidSetMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
    QMC5883_f32GetInitialHeading();
}

void QMC5883_voidSetMode(u16 mode, u16 odr, u16 rng, u16 osr)
{
    QMC5883_voidWriteRegister(0x09,mode|odr|rng|osr);
}

void QMC5883_voidWriteRegister(u8 Reg, u8 val)
{
    I2C_charWrite(I2CBUS,address,Reg, val);
}

void QMC5883_voidSoftReset(void)
{
    QMC5883_voidWriteRegister(0x0A,0x80);
}


u16 QMC5883_u16Read(short* x, short* y, short* z)
{
    char sensordata[7];
    I2C_charWrite(I2CBUS,address,0, 0x00);
    I2C_charRead(I2CBUS, address, 0, 7, sensordata);
    *x = (short) ( (sensordata[1] << 8 ) |sensordata[0] );
    *y = (short) ( (sensordata[3] << 8 ) |sensordata[2] );
    *z = (short) ( (sensordata[5] << 8 ) |sensordata[4] );
    char overflow = sensordata[6] & 0x02;
    return overflow << 2;
}
f32 QMC5883_f32GetAzimuth(pu16 a, pu16 b){
  f32 azimuth = atan2((u16)*a,(u16)*b) * 180.0/PI;
  return azimuth < 0?360 + azimuth:azimuth;
}
void QMC5883_f32GetInitialHeading()
{
    short x,y,z;
    QMC5883_u16Read(&x, &y, &z);

    x = (0.029975 * (x - 1358.944534) + 0.002137 * (y + 366.800852) - 0.005795 * (z - 1175.440578));
    y = (0.002137 * (x - 1358.944534) + 0.036549 * (y + 366.800852) - 0.001469 * (z - 1175.440578));
    z = (-0.005795 * (x - 1358.944534) - 0.001469 * (y + 366.800852) + 0.031086 * (z - 1175.440578));

    x = (1.177870 * (x - 7.020898) - 0.037572 * (y - 2.888513) + 0.195462 * (z - 2.089576));
    y = (-0.037572 * (x - 7.020898) + 0.968025 * (y - 2.888513) - 0.072147 * (z - 2.089576));
    z = (0.195462 * (x - 7.020898) - 0.072147 * (y - 2.888513) + 1.084548 * (z - 2.089576));

    initial=atan2(x, y)/0.0174532925;
}

f32 QMC5883_f32GetHeading()
{
    short x,y,z;
    f32 heading;
    QMC5883_u16Read(&x, &y, &z);

    x = (0.029975 * (x - 1358.944534) + 0.002137 * (y + 366.800852) - 0.005795 * (z - 1175.440578));
    y = (0.002137 * (x - 1358.944534) + 0.036549 * (y + 366.800852) - 0.001469 * (z - 1175.440578));
    z = (-0.005795 * (x - 1358.944534) - 0.001469 * (y + 366.800852) + 0.031086 * (z - 1175.440578));

    x = (1.177870 * (x - 7.020898) - 0.037572 * (y - 2.888513) + 0.195462 * (z - 2.089576));
    y = (-0.037572 * (x - 7.020898) + 0.968025 * (y - 2.888513) - 0.072147 * (z - 2.089576));
    z = (0.195462 * (x - 7.020898) - 0.072147 * (y - 2.888513) + 1.084548 * (z - 2.089576));

    heading=(atan2(x, y)/0.0174532925);
    heading -= initial;
    if(abs(heading) > 180)
    {
      if(heading > 0)
      {
        heading -= 360;
      }
      else if(heading < 0)
      {
        heading += 360;
      }
    }
    heading *= -1;
    return heading;
}

