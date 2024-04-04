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
  setMotors(speed, 0, speed, 0);
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
  driveLeft(255);
}

void turnRight()
{
  driveRight(255);
}

void turnRightSlow()
{
  static unsigned long timer;
  static bool stateToggle;
  if(timer < millis())
  {
    stateToggle = !stateToggle;
    timer = millis() + 100 + (stateToggle ? 50 : 0);
  }
  if(stateToggle)
  {
    driveRight(210);
  }
  else
  {
    driveBack(255);
  }
}

void turnRightBack()
{
  setMotors(0, 190, 0, 255);  
}

void turnLeftBack()
{
  setMotors(0, 255, 0, 210);
}

void incrementPulseLeft()
{
  pulsesLeft++;
}

void incrementPulseRight()
{
  pulsesLeft++;
}

boolean isStuck()
{
  static long previousPulses = pulsesLeft;
  static long timer = millis();
  static int amountOfFailedPulses;
  
  if(timer <= millis())
  {
    if ((previousPulses + 3) < pulsesLeft)
    {
      amountOfFailedPulses = 0;
      previousPulses = pulsesLeft;
    }
    else
    {
      amountOfFailedPulses++;
    }
    if (amountOfFailedPulses >= 10)
    {
      return true;
    } 
    timer = millis() + 100;
  }
  
  return false;
}
