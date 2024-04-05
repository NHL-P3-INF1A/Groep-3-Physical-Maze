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

// ==== [ Drive forwards and right at 0-255 speed ] ===========================

void driveForwardRight(int speed)
{
  driveDirection = forward;
  setMotors(speed, 0, speed - 100, 0);
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

// ==== [ Turning left ] ======================================================

void turnLeft()
{
  driveLeft(255);
}

// ==== [ Turning right ] =====================================================

void turnRight()
{
  driveRight(255);
}

// ==== [ Turning right slowly ] ==============================================

void turnRightSlow()
{
  static unsigned long timer;
  static bool stateToggle;
  // If the timer expired, switch state
  if(timer < millis())
  {
    // Switching state
    stateToggle = !stateToggle;
    // reset timer
    timer = millis() + 100 + (stateToggle ? 50 : 0);
  }
  // Switch driving direction that is based on the current state toggle
  if(stateToggle)
  {
    driveRight(210);
  }
  else
  {
    driveBack(255);
  }
}

// ==== [ Go backwards and right ] ============================================

void turnRightBack()
{
  setMotors(0, 180, 0, 255);  
}

// ==== [ Go backwards and left ] =============================================

void turnLeftBack()
{
  setMotors(0, 255, 0, 180);
}

// ==== [ Interrupt left wheel ] ==============================================

void incrementPulseLeft()
{
  pulsesLeft++;
}

// ==== [ Interrupt right wheel ] =============================================

void incrementPulseRight()
{
  pulsesRight++;
}

// ==== [ Checking if bot stuck ] =============================================

void isStuck()
{
  static long previousLeftPulses = pulsesLeft;
  static long previousRightPulses = pulsesRight;
  static unsigned long timer = millis();
  static int amountOfFailedLeftPulses;
  static int amountOfFailedRightPulses;
  
  if(timer <= millis())
  {
    // If the left pulses are 3 the previous calculation, reset
    if ((previousLeftPulses + 3) < pulsesLeft)
    {
      amountOfFailedLeftPulses = 0;
      previousLeftPulses = pulsesLeft;
    }
    else
    {
      amountOfFailedLeftPulses++;
    }
    // If the right pulses are 3 than the previous calculation, reset
    if ((previousRightPulses + 3) < pulsesRight)
    {
      amountOfFailedRightPulses = 0;
      previousRightPulses = pulsesRight;
    }
    else
    {
      amountOfFailedRightPulses++;
    }
    // Reset timer
    timer = millis() + 100;
    // If both are stuck, set isCurrentlyStuck to both
    if (amountOfFailedLeftPulses >= 10 && amountOfFailedRightPulses >= 10)
    {
      isCurrentlyStuck = stuckBoth;
    }
    // If left is stuck, set isCurrentlyStuck to left
    else if (amountOfFailedLeftPulses >= 10)
    {
      isCurrentlyStuck = stuckLeft;
    }
    // If right is stuck, set isCurrentlyStuck to right
    else if (amountOfFailedRightPulses >= 10)
    {
      isCurrentlyStuck = stuckRight;
    }
    // If everything is good, then set isCurrentlyStuck to not stuck
    else
    {
      setPixelByName(LED_RIGHT_BACK, RED);
      isCurrentlyStuck = notStuck;
    }
  }
}