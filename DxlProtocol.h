#ifndef DXL_PROTOCOL_H
#define DXL_PROTOCOL_H

#include <Arduino.h>

enum DXLInstruction{
  INST_PING = 0x01,
  INST_READ = 0x02,
  INST_WRITE = 0x03,
  INST_REBOOT = 0x08
};

enum DXLPacketError{
  ERR_NONE = 0x00,
  ERR_RESULT_FAIL,
  ERR_INST_ERROR,
  ERR_CRC_ERROR,
  ERR_DATA_RANGE,
  ERR_DATA_LENGTH,
  ERR_DATA_LIMIT,
  ERR_ACCESS  
};

typedef struct ControlTableDataInfo {
  uint8_t addr;
  uint8_t len;
} DXLDataInfo;

typedef struct _Packet {
  byte* data;
  uint16_t len;
} Packet;

Packet makePacket(uint8_t id, DXLInstruction inst, byte* param, uint16_t paramLen);
Packet makeReadPacket(uint8_t id, DXLDataInfo info);
Packet makeWritePacket(uint8_t id, DXLDataInfo info, int32_t content);

uint32_t decodeUnsignedPacked(Packet packet, uint8_t valueLen);
int32_t decodeSignedPacket(Packet packet, uint8_t valueLen);
bool checkPacket(Packet packet);
void printPacket(Packet packet);

#endif
