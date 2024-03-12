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
  setMotors(speed, 0 , speed, 0);
  driveDirection = forward;
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
  setPixelByName(LED_LEFT_FRONT, ORANGE);
  delay(380);
  driveStop();
  setPixelRgb(LED_LEFT_FRONT, 255, 255, 255);
}

void turnRight()
{
  driveRight(255);
  setPixelByName(LED_RIGHT_FRONT, ORANGE);
  delay(380);
  driveStop();
  setPixelRgb(LED_RIGHT_FRONT, 255, 255, 255);
}

void turnBack()
{
  driveLeft(255);
  delay(760);
  driveStop();
}

void incrementPulseLeft()
{
  pulsesLeft++;
}

void incrementPulseRight()
{
  pulsesRight++;
}
