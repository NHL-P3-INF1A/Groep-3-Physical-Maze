bool detectWall()
{
  // Stop if distance is less than or equal to stopDistance
  return (distanceFromObject() <= STOP_DISTANCE) ? true : false;
}

double distanceFromObject()
{
  digitalWrite(ECHO_SEND, LOW);
  delayMicroseconds(2);
  digitalWrite(ECHO_SEND, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHO_SEND, LOW);
  return pulseIn(ECHO_READ, HIGH) * 0.034 / 2;
}
