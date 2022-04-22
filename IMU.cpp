#include "IMU.h"

IMU::IMU(): wire_(Wire) {
  wire_.begin();
}

void IMU::setCLKConfig() {
  wire_.beginTransmission(MPU_ADDR);
  wire_.write(PWR_MGMT_1);
  wire_.write(0);
  wire_.endTransmission(true);
  return;
}

void IMU::setGyroConfig() {
  wire_.beginTransmission(MPU_ADDR);
  wire_.write(GYRO_CONFIG);
  wire_.write(0);
  wire_.endTransmission(true);
  return;
}

void IMU::setAccConfig() {
  wire_.beginTransmission(MPU_ADDR);
  wire_.write(ACCEL_CONFIG);
  wire_.write(0);
  wire_.endTransmission(true);
  return;
}

void IMU::calibration() {
  for (uint8_t cnt=0; cnt<10; cnt++) {
    this->getAcc();
    for (uint8_t i=0; i<XYZ; i++) { acc_offset[i]+=acc[i]; }
    this->getGyro();
    for (uint8_t i=0; i<XYZ; i++) { gyro_offset[i]+=gyro[i]; }
    delay(50);
  }
  for (uint8_t i=0; i<XYZ; i++) { 
    acc_offset[i]/=10;
    gyro_offset[i]/=10;
  }
  return;
}

void IMU::init() {
  this->setCLKConfig();
  this->setGyroConfig();
  this->setAccConfig();
  this->calibration();
  return;
}

int16_t* IMU::getAcc() {
  wire_.beginTransmission(MPU_ADDR);
  wire_.write(ACCEL_XOUT_H);
  wire_.endTransmission(false);
  wire_.requestFrom(MPU_ADDR, 2*XYZ, true);
  for(uint8_t i=0; i<XYZ; i++) acc[i] = (wire_.read() << 8) | wire_.read();
  return acc;
}

int16_t* IMU::getGyro() {
  wire_.beginTransmission(MPU_ADDR);
  wire_.write(GYRO_XOUT_H);
  wire_.endTransmission(false);
  wire_.requestFrom(MPU_ADDR, 2*XYZ, true);
  for(uint8_t i=0; i<XYZ; i++) gyro[i] = (wire_.read() << 8) | wire_.read();
  return gyro;
}
