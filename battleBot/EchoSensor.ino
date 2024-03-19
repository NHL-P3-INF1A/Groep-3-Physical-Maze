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


// ==== [ Test ] ==============================================================


// DetectWall en distanceFromObject combineren
// Wanneer hij naar voren kijkt en al voor 90/120cm ziet dat er niks is, ga dan naar links kijken

void checkPassage()
{
  static long pulseOffset = 0;

  if (distanceFromNextWall == 0)
  {
    echoSensorForward();
    delay(1000);
    distanceFromNextWall = distanceFromObject();
    echoSensorLeft();
    delay(1000);
  }

  if ((pulsesToCentimeters((pulsesLeft - pulseOffset)) + 5) >= distanceFromNextWall)
  {
    driveStop();
    if (!detectWall())
    {
      while(abs(rotationInDegrees - wantedRotation) <= 3)
      {
        turnLeft();
        updateRotation();
      }
      distanceFromNextWall = 0;
      pulseOffset = pulsesLeft;
      return;
    }
    echoSensorForward();
    delay(1000);
    if(!detectWall())
    {
      distanceFromNextWall = distanceFromObject();
      return;
    }

    echoSensorRight();
    delay(1000);
    if (!detectWall())
    {
      while(abs(rotationInDegrees - wantedRotation) <= 3)
      {
        turnRight();
        updateRotation();
      }
      distanceFromNextWall = 0;
      pulseOffset = pulsesLeft;
    }
    else
    {
      while(abs(rotationInDegrees - wantedRotation) <= 3)
      {
        turnBack();
        updateRotation();
      }
      distanceFromNextWall = 0;
      pulseOffset = pulsesLeft;
    }
  }

  if (!detectWall())
  {
    while(abs(rotationInDegrees - wantedRotation) <= 3)
    {
      turnLeft();
      updateRotation();
    }
    distanceFromNextWall = 0;
    pulseOffset = pulsesLeft;
  }
}
