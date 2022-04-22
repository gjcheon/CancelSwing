#ifndef IMU_H
#define IMU_H

#include <Wire.h>
#include <Arduino.h>

#define XYZ 3

#define MPU_ADDR 0x68

enum RegisterAddress{
  GYRO_CONFIG = 27,
  ACCEL_CONFIG = 28,
  ACCEL_XOUT_H = 59,
  GYRO_XOUT_H = 67,
  PWR_MGMT_1 = 107
};

class IMU {
public:
  IMU();
  void setCLKConfig();
  void setGyroConfig();
  void setAccConfig();
  void init();
  
  int16_t* getAcc();
  int16_t* getGyro();
  
  void calibration();
  
  
private:
  TwoWire& wire_;
  int16_t acc[XYZ];
  int16_t gyro[XYZ];
  int16_t acc_offset[XYZ];
  int16_t gyro_offset[XYZ];
};

#endif
