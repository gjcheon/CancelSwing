#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "DxlProtocol.h"

enum OPMode{
  CURRENT_CONTROL = 0,
  VELOCITY_CONTROL = 1,
  POSITION_CONTROL = 3,
  EXTENDED_POSITION_CONTROL = 4,
  CURRENT_BASED_POSITION_CONTROL = 5,
  PWM_CONTROL = 16
};


class Motor {
public:
  Motor(HardwareSerial& port, uint8_t id);
  void begin(unsigned long baud = 3000000);
  int32_t getPresentPosition();
  void setGoalPosition(uint16_t goal);
  void setTorqueOn();
  void setTorqueOff();
  void setLedOn();
  void setLedOff();
  void setOperatingMode(OPMode mode);
  
private:
  void write(Packet packet);
  Packet read();
  HardwareSerial& port_;
  uint8_t id_;  
};




#endif
