bool detectWall(int sensor, double distance)
{
  // Stop if distance is less than or equal to stopDistance
  return distanceFromObject(sensor) <= distance;
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
  double distance = pulseIn(echoRead, HIGH) * 0.034 / 2;
  if(distance > 60)
  {
    return 60;
  }
  return distance;
}
