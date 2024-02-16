double leftForwardOffset = 1;
double leftBackwardOffset = 1;    
double rightForwardOffset = 1;  
double rightBackwardOffset = 1;

// Drive sequence to calibrate the wheels
void calibrate()
{
    driveLeft(255);
    delay(1000);
    addPulses(4000, false, true);
    driveRight(255);
    delay(1000);
    addPulses(4000, true, false);
    driveStop();
}

// Collects pulses for the given time and sets offset values 
void addPulses(int time, bool leftForward, bool rightForward)
{
  int runtime = time + millis();
  int pulseLeftState;
  int pulseRightState;
  double pulsesLeft = 0;
  double pulsesRight = 0;
  while(millis() < runtime)
  {
    // Detects pulse on left side
    if(pulseLeftState != digitalRead(motorLeftRead))
    {
      pulseLeftState = digitalRead(motorLeftRead);
      pulsesLeft++;
    }
//    Serial.println();
//    Serial.println(pulsesLeft);
//    Serial.println(pulseLeftState);
    // Detects pulse on right side
    if(pulseRightState != digitalRead(motorRightRead))
    {
      pulseRightState = digitalRead(motorRightRead);
      pulsesRight++;
    }

    delay(10);
  }
  Serial.println(); 
  Serial.println(pulsesRight);
  Serial.println(pulsesLeft);
  double maxPulses = max(pulsesLeft, pulsesRight) + 0.00001;
  double leftOffset  = (float)pulsesLeft/maxPulses;
  double rightOffset = (float)pulsesRight/maxPulses;
//  Serial.println();
//  Serial.println(leftOffset);
//  Serial.println(rightOffset);
  if(leftForward)
  {
    leftBackwardOffset  = leftOffset;
  }
  else
  {
    leftForwardOffset   = leftOffset;
  }
  if(rightForward)
  {
    rightBackwardOffset = rightOffset;
  }
  else
  {
    rightForwardOffset  = rightOffset;
  }
  Serial.println(rightForwardOffset, 5);
  Serial.println(leftForwardOffset, 5);
  Serial.println(rightBackwardOffset, 5);
  Serial.println(leftBackwardOffset, 5);
}
