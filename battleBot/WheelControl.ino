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
      Serial.println("Go right");
    }
    else
    {
      setMotors(speed - 100, 0, speed, 0);
      Serial.println("Go left");
    } 
  } 
  else
  {
    setMotors(speed, 0, speed, 0);
    Serial.println("Go forward");
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

void turnLeft()
{
  turnToRelativeAxisAngle(90);
}

void turnRight()
{
  turnToRelativeAxisAngle(270);
}

void turnBack()
{
  turnToRelativeAxisAngle(180);
}

void incrementPulseLeft()
{
  pulsesLeft++;
}

void incrementPulseRight()
{
  pulsesRight++;
}

void turnToRelativeAxisAngle(double relativeRotation)
{ 
  static int angleToTurnTo;
  if (relativeRotation != wantedRotation)
  {
     wantedRotation = relativeRotation;
     angleToTurnTo = (int)(round(wrapAngle((rotationInDegrees + wantedRotation) / 90) * 90));
  }
  if(wantedRotation == 0)
  {
    return;
  }
  turnToAngle(angleToTurnTo);
}

void turnToAngle(double rotation)
{
  int driveSpeed;

  double rotationLeft = abs(rotation - rotationInDegrees);
  if(rotationLeft < 5)
  {
    driveSpeed = 0;
  }
  else
  {
    driveSpeed = 255;  
  }
  if(isRightTurnFaster(rotation))
  {
    driveRight(driveSpeed);  
  }
  else
  {
    driveLeft(driveSpeed);
  }
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
