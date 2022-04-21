#ifndef GLOBALVAR_H
#define GLOBALVAR_H

byte packetHeader[4] = {0xFF, 0xFF, 0xFD, 0x00};
bool torE[DXL_COUNT] = {false, false};
uint8_t pL, lastErrCode=0, nByte=0;
char readString[32];
uint16_t pos;
int init_pos;
unsigned long now=0, past=0;
double t;
bool sin_mode = false;

#endif
