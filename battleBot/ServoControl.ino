#define ECHO_SENSOR_FORWARD 1500
#define ECHO_SENSOR_RIGHT 500
#define ECHO_SENSOR_LEFT 2500

#define GRIPPER_OPEN 1500
#define GRIPPER_CLOSE 1000

void echoSensorForward()
{
  moveEchoSensor(ECHO_SENSOR_FORWARD);
}

void echoSensorLeft()
{
  moveEchoSensor(ECHO_SENSOR_LEFT);
}

void echoSensorRight()
{
  moveEchoSensor(ECHO_SENSOR_RIGHT);
}

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
  Serial.println("Still alive boi");
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

void moveEchoSensor(int pulseDuration)
{
  static unsigned long timer;
  static unsigned int pulse1 = 1500;
  if (pulseDuration > 0)
  {
    pulse1 = pulseDuration;
  }
  if(millis() > timer)
  {
    digitalWrite(ECHO_SERVO, HIGH);
    delayMicroseconds(pulse1);
    digitalWrite(ECHO_SERVO, LOW);
    timer = millis() + 20;
  }
}
