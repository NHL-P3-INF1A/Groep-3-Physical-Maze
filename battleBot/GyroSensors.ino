sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;

void updateRotation()
{
  lsm6ds3trc.getEvent(&accel, &gyro, &temp);
  static unsigned long timer;
  double interval = 100;
  double updatesPerSecond = (1000 / interval);
  if(millis() > timer)
  {
    double rotated = (radiansToDegrees(gyro.gyro.z) / updatesPerSecond);
    Serial.println(rotated);
    if (abs(rotated) < 0.2)
    {
      return;  
    }
    rotationInDegrees += rotated;
    timer = millis() + interval;  
  }  
  rotationInDegrees = wrapDegrees(rotationInDegrees);
}

double radiansToDegrees(double radians)
{
  return radians * (180 / PI);
}

double wrapDegrees(double degrees)
{
  if(degrees > 360)
  {
    return rotationInDegrees - 360;  
  }
  if(rotationInDegrees < 0)
  {
    return rotationInDegrees + 360;  
  }
}
