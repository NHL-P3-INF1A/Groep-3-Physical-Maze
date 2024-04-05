// ==== [ Check if averageColor is light ] ====================================

boolean isOnLightColor()
{
  int averageColor = 0;

  for (int sensorPin : IR_SENSORS)
  {
    averageColor += analogRead(sensorPin);
  }

  return (averageColor / 4) <= 800;
}

// ==== [ Check if left is light ] ============================================

boolean isLightOnLeft()
{
  return (analogRead(IR_SENSORS[0]) < 800);
}

// ==== [ Check if right is light ] ===========================================

boolean isLightOnRight()
{
  return (analogRead(IR_SENSORS[3]) < 800);
}

// ==== [ Check if any is black ] ==============================================

boolean isAnythingBlack()
{
  for (int pin : IR_SENSORS)
  {
    if (analogRead(pin) > 800)
    {
      return true;  
    }
  }

  return false;
}
