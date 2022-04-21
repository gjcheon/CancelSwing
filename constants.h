#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "CRC16.h"
#include "CRC.h"

#define DEBUG_SERIAL    Serial
#define YAW_MOTOR_SERIAL Serial3
#define PITCH_MOTOR_SERIAL Serial4
#define YAW_MOTOR_ID 0
#define PITCH_MOTOR_ID 1

// Settings
#define DXL_COUNT                       2
#define PACKET_LOG                      1
#define P_LOG                           1
#define READ_WAIT_US                    200

#define DXL_PROTOCOL_VERSION    2.0 

#define INST_PING     0x01
#define INST_READ     0x02
#define INST_WRITE    0x03
#define INST_REBOOT   0x08

#endif
