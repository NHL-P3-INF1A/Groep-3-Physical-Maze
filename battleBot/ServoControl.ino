#define ECHO_SENSOR_FORWARD 1500
#define ECHO_SENSOR_RIGHT 500
#define ECHO_SENSOR_LEFT 2500

#define GRIPPER_OPEN 1600
#define GRIPPER_CLOSE 1000

void echoSensorForward()
{
  moveGripper(ECHO_SENSOR_FORWARD, ECHO_SERVO);
}

void echoSensorLeft()
{
  moveGripper(ECHO_SENSOR_LEFT, ECHO_SERVO);
}

void echoSensorRight()
{
  moveGripper(ECHO_SENSOR_RIGHT, ECHO_SERVO);
}

void gripperOpen()
{
  moveGripper(GRIPPER_OPEN, GRIPPER_SERVO);
}

void gripperClose()
{
  moveGripper(GRIPPER_CLOSE, GRIPPER_SERVO);
}

void gripperUpdate()
{
  moveGripper(0, GRIPPER_SERVO);
}

void moveGripper(int pulseDuration, int servo)
{
  static unsigned long timer;
  static unsigned int pulse1;
  if (pulseDuration > 0)
  {
    pulse1 = pulseDuration;
  }
  if(millis() > timer)
  {
    digitalWrite(servo, HIGH);
    delayMicroseconds(pulse1);
    digitalWrite(servo, LOW);
    timer = millis() + 20;
  }
}
