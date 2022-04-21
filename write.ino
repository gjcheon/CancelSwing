void toggleTorque(uint8_t id) {
  torE[id] = !torE[id];
  pL = 3; byte param[pL] = {64, 0x00, torE[id]}; byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
  if (P_LOG) DEBUG_SERIAL.println("NOW TORQUE: " + String(torE[id]));
}

void setGoalPos(uint8_t id, uint16_t goal) {
  if (goal > 6000) {goal = 6000;}
  else if (goal < 0) {goal = 0;}
  pL = 6;
  byte param[pL] = {0x74, 0x00, (goal & 0xFF), goal >> 8, 0x00, 0x00};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setLedOn(uint8_t id) {
  pL = 3; byte param[pL] = {0x41, 0x00, 0x01}; byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setLedOff(uint8_t id) {
  pL = 3; byte param[pL] = {0x41, 0x00, 0x00}; byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setReturnDelay(uint8_t id, uint8_t delayTime) {
  pL = 3; byte param[pL] = {0x09, 0x00, 0x00}; byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setCurrentLimit(uint8_t id, uint16_t limitVal) {
  if (limitVal > 1193) limitVal = 1193;
  pL = 4; byte param[pL] = {38, 0x00, (limitVal & 0xFF), limitVal >> 8};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setOperationMode(uint8_t id, uint8_t om) {
  pL = 3; byte param[pL] = {0x0B, 0x00, om};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setGoalCurrent(uint8_t id, int16_t gC) {  
  if (gC > 1193) gC = 1193;
  else if (gC < -1193) gC = -1193;
  pL = 4; byte param[pL] = {102, 0x00, (gC & 0xFF), gC >> 8};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}

void setPosMax(uint8_t id, uint16_t posMax){
  if (posMax > 4096) posMax = 4096;
  pL = 6; byte param[pL] = {48, 0x00, (posMax & 0xFF), posMax >> 8};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setPosMin(uint8_t id, uint16_t posMin){
  if (posMin > 4096) posMin = 4096;
  pL = 6; byte param[pL] = {48, 0x00, (posMin & 0xFF), posMin >> 8};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
void setPWMLimit(uint8_t id, uint16_t limitVal) {
  if (limitVal > 885) limitVal = 885;
  pL = 4; byte param[pL] = {36, 0x00, (limitVal & 0xFF), limitVal >> 8};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}

void setGoalPWM(uint8_t id, int16_t gPWM) {  
  if (gPWM > 885) gPWM = 885;
  else if (gPWM < -885) gPWM = -885;
  pL = 4; byte param[pL] = {100, 0x00, (gPWM & 0xFF), gPWM >> 8};
  byte* sPc = makePacket(id, pL, INST_WRITE, param);
  lastErrCode = writeAndRead(id, sPc, pL+10);
  free(sPc);
}
