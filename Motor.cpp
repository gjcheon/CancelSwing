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
  //DEBUG_SERIAL.printf("goal position to %d\n", pos);
  Packet tPacket = makeWritePacket(id_, GoalPosition, pos);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setTorqueOn() {
  DEBUG_SERIAL.println("Torque ON");
  Packet tPacket = makeWritePacket(id_, TorqueEnable, 1);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setTorqueOff() {
  DEBUG_SERIAL.println("Torque OFF");
  Packet tPacket = makeWritePacket(id_, TorqueEnable, 0);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setLedOn() {
  DEBUG_SERIAL.println("LED ON");
  Packet tPacket = makeWritePacket(id_, LED, 1);
  this->write(tPacket);
  free(tPacket.data);
  Packet rPacket = this->read();
  free(rPacket.data);
  return;
}

void Motor::setLedOff() {
  DEBUG_SERIAL.println("LED OFF");
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
  if (transmitLen != tPacket.len) { DEBUG_SERIAL.printf("id: %d device wrong transmission\n", id_); } 
}

Packet Motor::read() {
  uint8_t startLen = 7;
  Packet rPacket;
  rPacket.data = (byte*) malloc(startLen * sizeof(byte));
  rPacket.len = startLen;

  delayMicroseconds(250);
  uint16_t idx = 0;
  while(port_.available()){
    rPacket.data[idx] = port_.read();
    if (startLen-1 == idx) {
      rPacket.len += (rPacket.data[5] + ((uint16_t)rPacket.data[6] << 8));
      rPacket.data = (byte*) realloc(rPacket.data, rPacket.len * sizeof(byte));
      delayMicroseconds(50);
    } 
    if (startLen != rPacket.len && rPacket.len-1 == idx) { break; }
    idx++;
  }
  if (rPacket.data[4] != id_) { DEBUG_SERIAL.println("received packet with wrong id"); printPacket(rPacket); }
  if (!checkPacket(rPacket)) { DEBUG_SERIAL.printf("id: %d device received invalid packet\n", id_); printPacket(rPacket); }
    
  return rPacket; 
}
