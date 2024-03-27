bool detectWall(int sensor)
{
  // Stop if distance is less than or equal to stopDistance
  return (distanceFromObject(sensor) <= STOP_DISTANCE) ? true : false;
}

double distanceFromObject(int sensor[])
{
  int echoRead = sensor[0];
  int echoSend = sensor[1];
  digitalWrite(echoSend, LOW);
  delayMicroseconds(2);
  digitalWrite(echoSend, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoSend, LOW);
  return pulseIn(echoRead, HIGH) * 0.034 / 2;
}
