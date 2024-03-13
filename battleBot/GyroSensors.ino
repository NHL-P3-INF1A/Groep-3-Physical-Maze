sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;

void updateRotation()
{
  lsm6ds3trc.getEvent(&accel, &gyro, &temp);
  static unsigned int timer;
  double interval = 100;
  if(millis() > timer)
  {
    double rotated = (radiansToDegrees(gyro.gyro.z) / 10);
    Serial.println(rotationInDegrees);
    if(abs(rotated) > 0.15)
    {
      rotationInDegrees += rotated;
      if(rotationInDegrees > 360)
      {
        rotationInDegrees -= 360;  
      }
      if(rotationInDegrees < 0)
      {
        rotationInDegrees += 360;  
      }
      Serial.println(isRightTurnFaster(90));
    }

    timer = millis() + interval;  
  }  
}

double radiansToDegrees(double radians)
{
  return radians * (180 / PI);
}
