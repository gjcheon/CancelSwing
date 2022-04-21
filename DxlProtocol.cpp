#include "DxlProtocol.h"
#include "CRC16.h"
#include "CRC.h"
#include "utils.h"

byte packetHeader[4] = {0xFF, 0xFF, 0xFD, 0x00};

Packet makePacket(uint8_t id, DXLInstruction inst, byte* param, uint8_t paramLen) {
  Packet packet;
  packet.len = 10 + paramLen;
  packet.data = (byte*) malloc(packet.len * sizeof(byte));
  memcpy(packet.data, packetHeader, 4);
  packet.data[4] = id;
  packet.data[5] = (paramLen + 3) & 0xFF;
  packet.data[6] = (paramLen + 3) >> 8;
  packet.data[7] = inst;
  if (paramLen > 0) { memcpy(&packet.data[8], param, paramLen); free(param); }
  uint16_t crcInt =  crc16((uint8_t *)packet.data, packet.len - 2, 0x8005, 0, 0, false, false);  
  packet.data[packet.len-2] = crcInt & 0xFF;
  packet.data[packet.len-1] = crcInt >> 8;
  return packet;  
}

Packet makeReadPacket(uint8_t id, DXLDataInfo info) {
  uint8_t paramLen = 4;
  byte* param = (byte*) malloc(paramLen * sizeof(byte));
  param[0] = info.addr & 0xFF;
  param[1] = info.addr >> 8;
  param[2] = info.len & 0xFF;
  param[3] = info.len >> 8;
  return makePacket(id, INST_READ, param, paramLen);
}

Packet makeWritePacket(uint8_t id, DXLDataInfo info, int32_t content) {
  uint8_t paramLen = 2 + info.len;
  byte* param = (byte*) malloc(paramLen * sizeof(byte));
  param[0] = info.addr & 0xFF;
  param[1] = info.addr >> 8;
  for (uint8_t i=0; i<info.len; i++) {
    param[2+i] = (content >> (8 * i)) & 0xFF;
  }
  return makePacket(id, INST_WRITE, param, paramLen);
}

uint32_t decodeUnsignedPacket(Packet packet, uint8_t valueLen) {
  uint32_t ret = 0;
  for (uint8_t i=0; i<valueLen; i++) {
    ret += (uint32_t)packet.data[9+i] << (8 * i);
  }
  return ret;
}


int32_t decodeSignedPacket(Packet packet, uint8_t valueLen) {
  return (int32_t) decodeUnsignedPacket(packet, valueLen);
}

bool checkPacket(Packet packet) {
  switch(packet.data[8]) {
    case ERR_RESULT_FAIL:
      DEBUG_SERIAL.println("Fail to process the sent Instruction Packet"); return false;
    case ERR_INST_ERROR:
      DEBUG_SERIAL.println("Undefined Instruction has been used"); return false;
    case ERR_CRC_ERROR:
      DEBUG_SERIAL.println("CRC of the sent Packet does not match"); return false;
    case ERR_DATA_RANGE:
      DEBUG_SERIAL.println("Data to be written in the corresponding Address is outside the range of the minimum/maximum value"); return false;
    case ERR_DATA_LENGTH:
      DEBUG_SERIAL.println("Attempt to write Data that is shorter than the data length of the corresponding Address"); return false;
    case ERR_DATA_LIMIT:
      DEBUG_SERIAL.println("Data to be written in the corresponding Address is outside of the Limit value"); return false;
    case ERR_ACCESS:
      DEBUG_SERIAL.println("Attempt to read/write value in prohibited region"); return false;
    default:
      break;
  }
  
  uint16_t crcInt1 =  crc16((uint8_t *) packet.data, packet.len - 2, 0x8005, 0, 0, false, false);  
  uint16_t crcInt2 =  ((uint16_t)packet.data[packet.len-1] << 8) + packet.data[packet.len-2];
  return (crcInt1 == crcInt2);
}

void printPacket(Packet packet) {
  for(uint8_t i=0; i<packet.len; i++){
    DEBUG_SERIAL.print(packet.data[i], HEX);
    DEBUG_SERIAL.print(" ");
  }
  DEBUG_SERIAL.println("------");
  return;
}
