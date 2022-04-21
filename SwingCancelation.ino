
#include "constants.h"
#include "globalvar.h"


void setup() {
  // put your setup code here, to run once:
  startDebugSerial();
  startDXLSerials();
  nByte = 0;
  
  now = millis();
  past = now;
}

void loop() {
  
  String command = "";
  while (DEBUG_SERIAL.available()) {
    delay(3);  //delay to allow buffer to fill 
    if (DEBUG_SERIAL.available() >0) {
      char c = DEBUG_SERIAL.read();  //gets one byte from serial buffer
      command += c;
    }
  }
  command.remove(command.length()-1);


  getPresentPos(YAW_MOTOR_ID);
  int yaw_motor_pos = LE2int32(&readString[9]);
  getPresentPos(PITCH_MOTOR_ID);
  int pitch_motor_pos = LE2int32(&readString[9]);
  DEBUG_SERIAL.print("yaw motor: ");
  DEBUG_SERIAL.print(yaw_motor_pos);
  DEBUG_SERIAL.print(", pitch motor: ");
  DEBUG_SERIAL.println(pitch_motor_pos);
  
  if (command == "on") {
    toggleTorque(PITCH_MOTOR_ID);
    sin_mode = true;
    t=0;
  } else if (command == "off") {
    setGoalPos(PITCH_MOTOR_ID, 1000);
    delay(1000);
    toggleTorque(PITCH_MOTOR_ID);
    sin_mode = false;
  }

  if (sin_mode) {
    pos = 1000 + 500*sin(t);
    setGoalPos(PITCH_MOTOR_ID, pos); 
    t += 0.01;
  }
  past = now;
  now = millis();
}
