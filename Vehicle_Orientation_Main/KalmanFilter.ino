#include <Wire.h> //Wire Librarey for I2C communication 
#include <MechaQMC5883.h> //QMC5883 Librarey is added since mine is QMC583 and not HMC5883

MechaQMC5883 qmc; //Create an object name for the snsor, I have named it as qmc
float initial,heading, angle;
float previous_heading;
void getOffset();
void getHeading();

int turns = 0;

int gyro_x, gyro_y, gyro_z;
long acc_x, acc_y, acc_z, acc_total_vector;
int temperature;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
long loop_timer;
int lcd_loop_counter;
float angle_pitch, angle_roll, angle_yaw;
int angle_pitch_buffer, angle_roll_buffer;
boolean set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;

float P00 = 0.0f, P01 = 0.0f, P10 = 0.0f, P11 = 0.0f;
float R = 200;
float sigma1 = 0.001f, sigma2 = 0.003f;
float Corrected_Angle = 0.0f;
float Corrected_Rate = 0.0f;
float bias = 0.0f;

float getAngle(float newAngle, float newRate);

void setup() {
  Wire.begin(); //Begin I2C communication 
  Serial.begin(115200); //Begin Serial Communication 
  getOffset();
  
  setup_mpu_6050_registers();                                          //Setup the registers of the MPU-6050 (500dfs / +/-8g) and start the gyro
  
  loop_timer = micros();                                               //Reset the loop timer
}

void loop() { //Infinite Loop
  getHeading();

  read_mpu_6050_data();                                                //Read the raw acc and gyro data from the MPU-6050

  
  //Gyro angle calculations
  //0.0000611 = 1 / (250Hz / 65.5)
  angle_pitch += gyro_x * 0.0000611;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
  angle_roll += gyro_y * 0.0000611;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
  angle_yaw += (gyro_z - bias) * 0.0000611;

  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
  
  //Place the MPU-6050 spirit level and note the values in the following two lines for calibration
  angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;                                            //Set the IMU started flag
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;      //Take 90% of the output roll value and add 10% of the raw roll value


  if((angle_yaw > 0) && (heading < 0) && (abs(angle_yaw - heading) > 180))
  {
    heading += 360;
  }
  else if((angle_yaw < 0) && (heading > 0) && (abs(angle_yaw - heading) > 180))
  {
    heading -= 360;
  }

if(abs(turns) < 1)
{
  if((gyro_z > bias) && (previous_heading - heading > 300))
  {
    turns++;
  }
  else if((gyro_z < bias) && (heading - previous_heading > 300))
  {
    turns--;
  }
}

  previous_heading = heading;
  
  Corrected_Angle = getAngle(heading, gyro_z);

  Serial.print(heading);
  Serial.print(' ');
  Serial.print(angle_yaw);
  Serial.print(' ');
  Serial.println(Corrected_Angle);
  
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer
}



float getAngle(float newAngle, float newRate)
{
  if(abs(angle - newAngle) > 300)
  {
    angle = newAngle;
  }
  Corrected_Rate = gyro_z - bias;
  angle += Corrected_Rate * 0.0000611 * 90.0 / 70.0;
  if(angle > 400)
{
  turns = 0;
  angle_yaw -= 360;
  angle -= 360;
  heading -= 360;
  previous_heading -= 360;
}
else if(angle < -400)
{
  turns = 0;
  angle_yaw += 360;
  angle += 360;
  heading += 360;
  previous_heading += 360;
}
  P00 += 0.004 * (0.004 * P11 - P01 - P10 + sigma1);
  P01 -= 0.004 * P11;
  P10 -= 0.004 * P11;
  P11 += sigma2 * 0.004;

  float S = P00 + R;

  float K[2]; // Kalman gain - This is a 2x1 vector
  K[0] = P00 / S;
  K[1] = P10 / S;

  float y = newAngle - angle; // Angle difference
  angle += K[0] * y;
  bias += K[1] * y;

  float P00_temp = P00;
  float P01_temp = P01;  

  P00 -= K[0] * P00_temp;
  P01 -= K[0] * P01_temp;
  P10 -= K[1] * P00_temp;
  P11 -= K[1] * P01_temp;

  return angle;

}

void read_mpu_6050_data(){                                             //Subroutine for reading the raw gyro and accelerometer data
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  acc_x = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_x variable
  acc_y = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_y variable
  acc_z = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_z variable
  temperature = Wire.read()<<8|Wire.read();                            //Add the low and high byte to the temperature variable
  gyro_x = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_x variable
  gyro_y = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_y variable
  gyro_z = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_z variable

}

void setup_mpu_6050_registers(){
  //Activate the MPU-6050
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
}


void getOffset()
{
  qmc.init(); //Initialise the QMC5883 Sensor
  int x,y,z;
  qmc.read(&x,&y,&z); //Get the values of X,Y and Z from sensor  

  x = (0.029975 * (x - 1358.944534) + 0.002137 * (y + 366.800852) - 0.005795 * (z - 1175.440578));
  y = (0.002137 * (x - 1358.944534) + 0.036549 * (y + 366.800852) - 0.001469 * (z - 1175.440578));
  z = (-0.005795 * (x - 1358.944534) - 0.001469 * (y + 366.800852) + 0.031086 * (z - 1175.440578));
  
  x = (1.177870 * (x - 7.020898) - 0.037572 * (y - 2.888513) + 0.195462 * (z - 2.089576));
  y = (-0.037572 * (x - 7.020898) + 0.968025 * (y - 2.888513) - 0.072147 * (z - 2.089576));
  z = (0.195462 * (x - 7.020898) - 0.072147 * (y - 2.888513) + 1.084548 * (z - 2.089576));
  


  int heading=atan2(x, y)/0.0174532925;
  initial = heading;
}
void getHeading()
{
  int x,y,z;
  qmc.read(&x,&y,&z); //Get the values of X,Y and Z from sensor 

  x = (0.029975 * (x - 1358.944534) + 0.002137 * (y + 366.800852) - 0.005795 * (z - 1175.440578));
  y = (0.002137 * (x - 1358.944534) + 0.036549 * (y + 366.800852) - 0.001469 * (z - 1175.440578));
  z = (-0.005795 * (x - 1358.944534) - 0.001469 * (y + 366.800852) + 0.031086 * (z - 1175.440578));
  

  x = (1.177870 * (x - 7.020898) - 0.037572 * (y - 2.888513) + 0.195462 * (z - 2.089576));
  y = (-0.037572 * (x - 7.020898) + 0.968025 * (y - 2.888513) - 0.072147 * (z - 2.089576));
  z = (0.195462 * (x - 7.020898) - 0.072147 * (y - 2.888513) + 1.084548 * (z - 2.089576));

heading=(atan2(x, y)/0.0174532925) - initial; //Calculate the degree using X and Y parameters with this formulae
if(abs(heading) > 180 * (abs(turns) + 1))
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

  heading += (360 * turns);


}
