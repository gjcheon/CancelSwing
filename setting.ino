
void startDebugSerial(){
  DEBUG_SERIAL.begin(115200);
  DEBUG_SERIAL.println("BEGIN!!");
}

void startDXLSerials(){
  YAW_MOTOR_SERIAL.begin(3000000, SERIAL_8N1_HALF_DUPLEX);
  PITCH_MOTOR_SERIAL.begin(3000000, SERIAL_8N1_HALF_DUPLEX);

  while (!(YAW_MOTOR_SERIAL)) {DEBUG_SERIAL.println("YAW_MOTOR DELAY"); delay(1);}
  while (!(PITCH_MOTOR_SERIAL)) {DEBUG_SERIAL.println("PITCH_MOTOR DELAY"); delay(1);}
}
