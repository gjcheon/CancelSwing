#include "Motor.h"
#include "utils.h"

Motor pitch_motor(Serial2, 1);
Motor yaw_motor(Serial3, 0);
bool sin_mode = false;
double t=0;

void setup() {
  DEBUG_SERIAL.begin(115200);
  DEBUG_SERIAL.println("BEGIN");
  yaw_motor.begin();
  pitch_motor.begin();
}

void loop() {
  /*int yaw = yaw_motor.getPresentPosition();
  int pitch = pitch_motor.getPresentPosition();
  DEBUG_SERIAL.printf("yaw: %d", yaw);
  DEBUG_SERIAL.printf(", pitch: %d\n", pitch);*/

  String command = "";
  while (DEBUG_SERIAL.available()) {
    delay(3);
    if (DEBUG_SERIAL.available() > 0) {
      char c = DEBUG_SERIAL.read();
      command += c;
    }
  }
  command.remove(command.length()-1);

  if (command == "on") {
    DEBUG_SERIAL.println("sin mode");
    sin_mode = true;
    yaw_motor.setOperatingMode(POSITION_CONTROL);
    yaw_motor.setTorqueOn();
    yaw_motor.setLedOn();
  } else if (command == "off") {
    sin_mode = false;
    yaw_motor.setGoalPosition(1000);
    delay(500);
    yaw_motor.setTorqueOff();
    yaw_motor.setLedOff();
    t=0;
  }

  if (sin_mode) {
    uint16_t pos = 1000 + (uint16_t)(1000*sin(t/30.0));
    yaw_motor.setGoalPosition(pos);
    t++;
  }
    
  delay(50);
}
