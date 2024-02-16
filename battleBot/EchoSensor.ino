bool detectWall()
{
  // Stop if distance is less than or equal to stopDistance
  return (distanceFromObject() <= stopDistance) ? true : false;
}

double distanceFromObject()
{
  digitalWrite(echoPinSend, LOW);
  delayMicroseconds(2);
  digitalWrite(echoPinSend, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPinSend, LOW);
  return pulseIn(echoPinRead, HIGH) * 0.034 / 2;
}