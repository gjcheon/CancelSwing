float* arrMulf(float* arr1, float* arr2){
  uint8_t n_arr = sizeof(arr1) / sizeof(float);
  float res[n_arr];
  for(uint8_t i=0; i<n_arr; i++) res[i] = arr1[i] * arr2[i];  
  return res;
}
float arrMulSumf(float* arr1, float* arr2){
  uint8_t n_arr = sizeof(arr1) / sizeof(float);
  float res = 0.0;
  for(uint8_t i=0; i<n_arr; i++) res += arr1[i] * arr2[i];  
  return res;
}
byte * makePacket(uint8_t targetID, uint8_t paramLen, uint8_t inst, byte* buff){  
  byte* sendBuf = (byte*) malloc((paramLen+10) * sizeof(byte));
  memcpy(sendBuf, packetHeader, 4);
  sendBuf[4] = targetID; sendBuf[5] = paramLen+3; sendBuf[6] = 0x00; sendBuf[7] = inst;
  if (paramLen > 0)  memcpy(&sendBuf[8], buff, paramLen);    
  uint16_t crcInt =  crc16((uint8_t *) sendBuf, paramLen+8, 0x8005, 0, 0, false, false);  
  sendBuf[paramLen+8] = crcInt & 0xFF; sendBuf[paramLen+9] = crcInt >> 8;
  
  if (PACKET_LOG){
    for(uint8_t i=0; (i<paramLen+10); i++){
      DEBUG_SERIAL.print(sendBuf[i], HEX);
      DEBUG_SERIAL.print(" ");
    }
    DEBUG_SERIAL.println("------");
  }
  return sendBuf;
}

uint16_t LE2uint16(uint8_t lsb, uint8_t msb){
  return (msb << 8) + lsb;
}

uint16_t LE2uint16(byte * addr){
  return (*(addr+1) << 8) + *addr;
}
uint16_t LE2uint16(uint8_t lsb, uint8_t msb, uint16_t cut){
  uint16_t res = (msb << 8) + lsb;
  if (res > cut) return 0;
  else return res;
}
uint32_t LE2uint32(byte * addr){
  uint32_t res = 0;
  for (uint8_t i=3; i>0; i--){
    res += *(addr+i) << (8 * i);
  }
  res += *addr;
  return res;
}
int16_t LE2int16(uint8_t lsb, uint8_t msb){
  return (int16_t) LE2uint16(lsb,msb);
}
int16_t LE2int16(byte * addr){
  return (int16_t) LE2uint16(addr);
}
int32_t LE2int32(byte * addr){
  return (int32_t) LE2uint32(addr);
}
void readfromDxl(uint8_t id){
  nByte = 0; 
  delayMicroseconds(READ_WAIT_US);
  if (id == YAW_MOTOR_ID) {
    while(YAW_MOTOR_SERIAL.available()){
      readString[nByte] = YAW_MOTOR_SERIAL.read(); 
      nByte ++; 
    }
  } else if (id == PITCH_MOTOR_ID) {
    while(PITCH_MOTOR_SERIAL.available()){
      readString[nByte] = PITCH_MOTOR_SERIAL.read(); 
      nByte ++; 
    }
  }

}
void printReadBuffer(){
  for (int i=0; i<nByte; i++){
    DEBUG_SERIAL.print(readString[i], HEX);  // print the result on UART
    DEBUG_SERIAL.print(" "); if (i==nByte-1) DEBUG_SERIAL.println();
  }  
}
bool readCheckCRC(byte * toCheck, uint8_t paramLen){
  uint16_t crcInt1 =  crc16((uint8_t *) toCheck, paramLen+7, 0x8005, 0, 0, false, false);  
  uint16_t crcInt2 =  (*(toCheck+paramLen+8) << 8) + (*(toCheck+paramLen+7));
  return (crcInt1 == crcInt2);
}

uint8_t writeAndRead(uint8_t id, byte* sPcc, uint8_t len){
  if (id == YAW_MOTOR_ID) {
    YAW_MOTOR_SERIAL.flush();
    YAW_MOTOR_SERIAL.write(sPcc, len);
  } else if (id == PITCH_MOTOR_ID) {
    PITCH_MOTOR_SERIAL.flush();
    PITCH_MOTOR_SERIAL.write(sPcc, len);
  }
  readfromDxl(id);
  return readString[8];
}
