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
  if (distanceFromNextWall = null)
  {
    echoSensorForward();
    delay(200);
    distanceFromNextWall = distanceFromObject();
    echoSensorLeft();
    delay(200);
  }

  if ((pulsesToCentimeters(pulsesLeft) + 15) >= distanceFromNextWall)
  {
    driveStop();
    if (!detectWall())
    {
      turnLeft();
      distanceFromNextWall = null;
      return;
    }

    echoSensorRight();
    delay(200);
    if (!detectWall())
    {
      turnRight();
      distanceFromNextWall = null;
    }
    else
    {
      turnBack();
      distanceFromNextWall = null;
    }
  }

    if (!detectWall())
    {
      turnLeft();
      distanceFromNextWall = null;
    }
}