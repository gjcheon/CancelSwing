#include "Motor.h"
#include "utils.h"

DXLDataInfo GoalPosition = {116, 4};
DXLDataInfo PresentPosition = {132, 4};
DXLDataInfo TorqueEnable = {64, 1};
DXLDataInfo OperatingMode = {11, 1};
DXLDataInfo LED = {65, 1};

Motor::Motor(HardwareSerial& port, uint8_t id):port_(port), id_(id) {}

void Motor::begin(unsigned long baud) {
  port_.begin(baud, SERIAL_8N1_HALF_DUPLEX);
}

int32_t Motor::getPresentPosition() {
  Packet tPacket = makeReadPacket(id_, PresentPosition);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  int pos = decodeSignedPacket(rPacket, PresentPosition.len);
  free(rPacket.data);
  return pos;
}

void Motor::setGoalPosition(uint16_t pos) {
  Packet tPacket = makeWritePacket(id_, GoalPosition, pos);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setTorqueOn() {
  Packet tPacket = makeWritePacket(id_, TorqueEnable, true);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setTorqueOff() {
  Packet tPacket = makeWritePacket(id_, TorqueEnable, false);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setLedOn() {
  Packet tPacket = makeWritePacket(id_, LED, 1);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setLedOff() {
  Packet tPacket = makeWritePacket(id_, LED, 0);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setOperatingMode(OPMode mode) {
  Packet tPacket = makeWritePacket(id_, OperatingMode, mode);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::write(Packet tPacket) {
  uint8_t transmitLen = port_.write(tPacket.data, tPacket.len);
  port_.flush();
  if (transmitLen != tPacket.len) DEBUG_SERIAL.printf("id: %d device wrong transmission\n", id_);  
}

Packet Motor::read() {
  uint8_t startLen = 7;
  Packet rPacket;
  rPacket.data = (byte*) malloc(startLen * sizeof(byte));
  rPacket.len = startLen;

  delayMicroseconds(200);
  uint16_t idx = 0;
  while(port_.available()){
    rPacket.data[idx] = port_.read();
    if (startLen-1 == idx) {
      rPacket.len += (rPacket.data[5] + ((uint16_t)rPacket.data[6] << 8));
      rPacket.data = (byte*) realloc(rPacket.data, rPacket.len * sizeof(byte));
    } 
    if (startLen != rPacket.len && rPacket.len-1 < idx) {
      DEBUG_SERIAL.printf("id: %d device received invalid length packet\n", id_);
    }
    idx++;
    delayMicroseconds(10);
  }
  if (rPacket.data[4] != id_) { DEBUG_SERIAL.println("received packet with wrong id"); }
  if (!checkPacket(rPacket)) { DEBUG_SERIAL.printf("id: %d device received invalid packet\n", id_); }
    
  return rPacket; 
}
