//TODO Remove when race day
void readIrOutput()
{
  for (int sensorPin : IR_SENSORS)
  {
    Serial.print(analogRead(sensorPin));
    Serial.print(" ");
  }
  Serial.print(" 800");
  Serial.println();
}

boolean isOnLightColor()
{
  int averageColor = 0;
  for (int sensorPin : IR_SENSORS)
  {
    averageColor += analogRead(sensorPin);
  }
  return (averageColor / 4) <= 800;
}
