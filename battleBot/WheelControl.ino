// ==== [ Sets motor power to input ] =========================================
void setMotors(int LFWD, int LBACK, int RFWD, int RBACK)
{
  analogWrite(MOTOR_LEFT_FORWARD,   LFWD);
  analogWrite(MOTOR_LEFT_BACK,  LBACK);
  analogWrite(MOTOR_RIGHT_FORWARD,  RFWD);
  analogWrite(MOTOR_RIGHT_BACK, RBACK);
}

// ==== [ Rotate left at 0-255 speed ] ========================================
void driveLeft(int speed)
{
  setMotors(0, speed, speed, 0);
  driveDirection = left;
}

// ==== [ Rotate right at 0-255 speed ] =======================================
void driveRight(int speed)
{
  setMotors(speed, 0 , 0, speed);
  driveDirection = right;
}

// ==== [ Drive forwards at 0-255 speed ] =====================================
void driveForward(int speed)
{
  driveDirection = forward;
  if (abs(rotationInDegrees - wantedRotation) > 2)
  {
    if (isRightTurnFaster(wantedRotation)) {
      setMotors(speed, 0, speed - 100, 0);
    }
    else
    {
      setMotors(speed - 100, 0, speed, 0);
    } 
  } 
  else
  {
    setMotors(speed, 0, speed, 0);
  }
}

// ==== [ Drive backwards at 0-255 speed ] ====================================
void driveBack(int speed)
{
  setMotors(0, speed, 0, speed);
  driveDirection = backwards;
}

// ==== [ Stop driving ] ======================================================
void driveStop()
{
  setMotors(0, 0, 0, 0);
  driveDirection = none;
}

boolean turnLeft()
{
  turnToRelativeAxisAngle(1);
  while(turnToRelativeAxisAngle(0));
  return true;
}

boolean turnRight()
{
  return turnToRelativeAxisAngle(2);
}

boolean turnBack()
{
  return turnToRelativeAxisAngle(3);
}

void incrementPulseLeft()
{
  pulsesLeft++;
}

void incrementPulseRight()
{
  pulsesRight++;
}

/*
boolean turnToRelativeAxisAngle(double relativeRotation)
{ 
  static int angleToTurnTo;
  if (relativeRotation != wantedRotation)
  {
     wantedRotation = relativeRotation;
     angleToTurnTo = (int)(round(wrapAngle((rotationInDegrees + wantedRotation) / 90) * 90));
  }
  turnToAngle(angleToTurnTo);
  if(abs(rotationInDegrees - wantedRotation) <= 3)
  {
    return true;
  }
  return false;
}
*/

boolean turnToRelativeAxisAngle(int relativeRotation)
{
  static int rotationOffset = rotationInDegrees;
  static int angleToTurnTo;
  static boolean isAtRotation = true;
  
  /*
   * 1 = to the left
   * 2 = to the right
   * 3 = 180 turn
   */
   
  switch(relativeRotation)
  {
    case 1:
      // Rotate 90 degrees compared to the current offset
      rotationOffset = wrapAngle(rotationOffset + 90);
      isAtRotation = false;
      break;
    case 2:
      // Rotate -90 degrees compared to the current offset
      rotationOffset = wrapAngle(rotationOffset - 90);
      isAtRotation = false;
      break;
    case 3:
      // Rotate 180 degrees compared to the current offset
      rotationOffset = wrapAngle(rotationOffset + 180);
      isAtRotation = false;
      break;
    case 0:
    default:
      Serial.println("Looping current rotation");
      // Keep looping current wanted rotation untill it has been reached
        updateRotation();
        turnToAngle(rotationOffset);
        if (abs(rotationInDegrees - rotationOffset) <= 5)
        { 
          Serial.println("HE BE STOPPIN'N");
          // If the rotation is within 5 degrees of the wanted rotation, assume it has arrived at destination
          isAtRotation = true;
        }
        if (!isAtRotation)
        {
          return true;
        }
        else
        {
          return false; 
        }
      break;
  }
}

void turnToAngle(double rotation)
{
  int driveSpeed;
  int rotationLeft = rotation - rotationInDegrees;  
  if(rotationLeft > 60)
  {
    driveSpeed = 200;  
  }
  else if (rotationLeft > 30)
  {
    driveSpeed = 180;
  }
  else if (rotationLeft > -30)
  {
    driveSpeed = 150;
  }
  else if (rotationLeft > -60)
  {
    driveSpeed = 180;
  }
  else
  {
    driveSpeed = 200;
  }
  if(rotationLeft < -90)
  {
      driveRight(driveSpeed);
  }
  else
  {
      driveLeft(driveSpeed);
  }
  Serial.println(rotationLeft);
  

}

bool isRightTurnFaster(double rotation)
{
  double rightDiffrence = wrapAngle(rotationInDegrees - rotation);
  double leftDiffrence = wrapAngle(rotation - rotationInDegrees);
  if(rightDiffrence > leftDiffrence)
  {
    return false;
  }
  else
  {
    return true;  
  }
}

double wrapAngle(int rotationToWrap)
{
  if(rotationToWrap > 360)
  {
    rotationToWrap -= 360;  
  }
  if(rotationToWrap < 0)
  {
    rotationToWrap += 360;  
  }
  return rotationToWrap;
}

double pulsesToCentimeters(int pulses)
{
    return ((pulses / 40) * 6.6 * PI);
}
