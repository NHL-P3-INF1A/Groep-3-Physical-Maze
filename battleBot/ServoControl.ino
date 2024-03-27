#define GRIPPER_OPEN 1500
#define GRIPPER_CLOSE 1000

void gripperOpen()
{
  moveGripper(GRIPPER_OPEN);
}

void gripperClose()
{
  moveGripper(GRIPPER_CLOSE);
}

void gripperUpdate()
{
  moveGripper(0);
}

void echoSensorUpdate()
{
  moveEchoSensor(0);
}

void moveGripper(int pulseDuration)
{
  static unsigned long timer;
  static unsigned int pulse1 = 1500;
  if (pulseDuration > 0)
  {
    pulse1 = pulseDuration;
  }
  if(millis() > timer)
  {
    digitalWrite(GRIPPER_SERVO, HIGH);
    delayMicroseconds(pulse1);
    digitalWrite(GRIPPER_SERVO, LOW);
    timer = millis() + 20;
  }
}
