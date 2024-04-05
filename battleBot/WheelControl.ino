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
  setMotors(0, 180, 0, 255);  
}

void turnLeftBack()
{
  setMotors(0, 255, 0, 180);
}

void incrementPulseLeft()
{
  pulsesLeft++;
}

void incrementPulseRight()
{
  pulsesRight++;
}

void isStuck()
{
  static long previousLeftPulses = pulsesLeft;
  static long previousRightPulses = pulsesRight;
  static unsigned long timer = millis();
  static int amountOfFailedLeftPulses;
  static int amountOfFailedRightPulses;
  
  if(timer <= millis())
  {
//    Serial.println("Attempting unstuck");
//    Serial.print("pulsesLeft: ");
//    Serial.println(pulsesLeft);
//    Serial.print("pulsesRight: ");
//    Serial.println(pulsesRight);
//    Serial.print("previousLeftPulses: ");
//    Serial.println(previousLeftPulses);
//    Serial.print("previousRightPulses: ");
//    Serial.println(previousRightPulses);
    Serial.print("amountOfFailedLeftPulses: ");
    Serial.println(amountOfFailedLeftPulses);
    Serial.print("amountOfFailedRightPulses: ");
    Serial.println(amountOfFailedRightPulses);
    if ((previousLeftPulses + 3) < pulsesLeft)
    {
      amountOfFailedLeftPulses = 0;
      previousLeftPulses = pulsesLeft;
    }
    else
    {
      amountOfFailedLeftPulses++;
    }
    if ((previousRightPulses + 3) < pulsesRight)
    {
      amountOfFailedRightPulses = 0;
      previousRightPulses = pulsesRight;
    }
    else
    {
      amountOfFailedRightPulses++;
    }
    timer = millis() + 100;
    if (amountOfFailedLeftPulses >= 10 && amountOfFailedRightPulses >= 10)
    {
      Serial.println("Running unstuck both");
      isCurrentlyStuck = stuckBoth;
    } 
    else if (amountOfFailedLeftPulses >= 10)
    {
      Serial.println("Running unstuck left");
      isCurrentlyStuck = stuckLeft;
    }
    else if (amountOfFailedRightPulses >= 10)
    {
      Serial.println("Running unstuck right");
      isCurrentlyStuck = stuckRight;
    }
    else
    {
      Serial.println("Resetting lights");
      setPixelByName(LED_RIGHT_BACK, RED);
      isCurrentlyStuck = notStuck;
    }
  }
}
