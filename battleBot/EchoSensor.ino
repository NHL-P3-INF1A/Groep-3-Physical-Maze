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

/*
 * Als er geen muur momenteel bekend is, check waar de volgende muur zit
 * als de muur wel bekend is, kijk naar links en ga naar voren
 * als er link een muur is, en vooruit ook, kijk naar rechts
 * als er rechts niets is, keer om en herhaal
 */

// ==== [ Check for wall ] ====================================================
boolean hasReachedWall()
{
  //centimers afgelegd groter dan de afstand tot de muur ? true : false
  if(distanceFromNextWall == -1)
  {
    echoSensorForward();
    delay(1000);
    distanceFromNextWall = distanceFromObject();
  }
  if((pulsesToCentimeters((pulsesLeft - pulseOffset)) + 5) >= distanceFromNextWall)
  {
    pulseOffset = pulsesLeft;
    return true;
  }
  else
  {
    return false;
  }
}

// ==== [ Recheck at destination ] ============================================
boolean checkIfYouCanStillGoForwardMore()
{
  if(hasReachedWall())
  {
    Serial.print("I have reached a wall");
    driveStop();
    echoSensorForward();
    delay(1000);
    if(!detectWall())
    {
       echoSensorLeft();
       delay(1000);
       return true;
    }
    else
    {
      return false;
    }
  }
  return true;
}

// ==== [ Continously look left ] =============================================
void checkLeftWallWhileDrivingForward()
{
  echoSensorLeft();
  if (!detectWall())
  {
    while(abs(rotationInDegrees - wantedRotation) <= 3)
    {
      turnLeft();
      updateRotation();
    }
    distanceFromNextWall = -1;
    pulseOffset = pulsesLeft;
    return;
  }
}

// == [ Go back when cornered ] ===============================================
boolean ifBothWallAndNothingLeftThen180()
{
  echoSensorRight();
  delay(1000);
  if (!detectWall())
  {
    while(abs(rotationInDegrees - wantedRotation) <= 3)
    {
      turnBack();
      updateRotation();
    }
    distanceFromNextWall = 0;
    pulseOffset = pulsesLeft;
    return true;
  }
  return false;
}

//Needs a better name
void smartForward()
{
  if(checkIfYouCanStillGoForwardMore())
  {
    checkLeftWallWhileDrivingForward();
    driveForward(200);
  }
}
