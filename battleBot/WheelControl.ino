// Sets motor power to input
void setMotors(int LFWD, int LBACK, int RFWD, int RBACK)
{
  analogWrite(motorLeftFwd,   LFWD * leftForwardOffset);
  analogWrite(motorLeftBack,  LBACK * leftBackwardOffset);
  analogWrite(motorRightFwd,  RFWD * rightForwardOffset);
  analogWrite(motorRightBack, RBACK * rightBackwardOffset);
}

// Rotate left at 0-255 speed
void driveLeft(int speed)
{
  setMotors(0, speed, speed, 0);
  driveDirection = left;
}

// Rotate right at 0-255 speed
void driveRight(int speed)
{
  setMotors(speed, 0 , 0, speed);
  driveDirection = right;
}

// Drive forwards at 0-255 speed
void driveForward(int speed)
{
  setMotors(speed, 0 , speed, 0);
  driveDirection = forward;
}

// Drive backwards at 0-255 speed
void driveBack(int speed)
{
  setMotors(0, speed, 0, speed);
  driveDirection = backwards;
}

// Stop driving
void driveStop()
{
  setMotors(0, 0, 0, 0);
  driveDirection = none;
}
