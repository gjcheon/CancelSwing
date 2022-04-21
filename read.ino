void ping(uint8_t id) {
  pL = 0; byte param[1] = {0x00}; byte* sPc = makePacket(id, pL, INST_PING, param); 
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void factory_reset(uint8_t id){
  pL=1; byte param[1] = {0x02}; byte* sPc = makePacket(id, pL, 0x06, param); 
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void reboot(uint8_t id){
  pL=0; byte param[1] = {0x00}; byte* sPc = makePacket(id, pL, INST_REBOOT, param); 
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getGoalCurrent(uint8_t id) {
  pL = 4; byte param[pL] = {102, 0x00, 0x02, 0x00};
  byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);  
  free(sPc);
}
void getModelNumber(uint8_t id) {
  pL = 4; byte param[pL] = {0x00, 0x00, 0x02, 0x00};
  byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getFirmwareVersion(uint8_t id) {
  pL = 4; byte param[pL] = {0x06, 0x00, 0x01, 0x00};
  byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getCurrentLimit(uint8_t id) {
  pL = 4; byte param[pL] = {38, 0x00, 0x02, 0x00};
  byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getPresentCurrent(uint8_t id) {
  pL = 4; byte param[pL] = {126, 0x00, 2, 0x00}; byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getPresentPos(uint8_t id) {
  pL = 4; byte param[pL] = {0x84, 0x00, 0x04, 0x00}; byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getOperationMode(uint8_t id) {
  pL = 4; byte param[pL] = {0x0B, 0x00, 0x01, 0x00}; byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getPresentPWM(uint8_t id) {
  pL = 4; byte param[pL] = {124, 0x00, 2, 0x00}; byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getGoalPWM(uint8_t id) {
  pL = 4; byte param[pL] = {100, 0x00, 0x02, 0x00};
  byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);  
  free(sPc);
}
void getTempLimit(uint8_t id) {
  pL = 4; byte param[pL] = {31, 0x00, 0x01, 0x00}; byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
void getPresentTemp(uint8_t id) {
  pL = 4; byte param[pL] = {146, 0x00, 0x01, 0x00}; byte* sPc = makePacket(id, pL, INST_READ, param);
  writeAndRead(id, sPc, pL + 10);
  free(sPc);
}
