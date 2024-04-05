// ==== [ Neopixel Setup ] ====================================================
#include <Adafruit_NeoPixel.h>
#define   LED_PIN                 8   // Pin that the neopixels are connected to
#define   LED_COUNT               4   // Amount of LEDs
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

// ==== [ Motor Pins ] ========================================================
#define   MOTOR_LEFT_BACK         12  // Motor A1 LB
#define   MOTOR_LEFT_FORWARD      11  // Motor A2 LF
#define   MOTOR_RIGHT_FORWARD     10  // Motor B1 RF
#define   MOTOR_RIGHT_BACK        6   // Motor B2 RB

#define   MOTOR_LEFT_READ         2   // Interrupt Left motor
#define   MOTOR_RIGHT_READ        3   // Interrupt right motor
#define   DRIVE_SPEED             255 // Speed at which it drives normally

// ==== [ Echo Sensor Pins ] ==================================================
const int ECHO_FORWARD[]        = {9, 4}; // {Echo Read, Echo Send}
const int ECHO_LEFT[]           = {5, A5}; // was 13
#define   STOP_DISTANCE           10  // Distance threshold to stop the robot (in cm)
#define   WALLHUG_DISTANCE        8  // Distance from the left wall


// ==== [ Gripper Pin ] =======================================================
#define   GRIPPER_SERVO           7   // Servo for front gripper

// ==== [ Led Layout ] ========================================================
#define   LED_LEFT_BACK           0   // Left Back
#define   LED_RIGHT_BACK          1   // Right Back
#define   LED_RIGHT_FRONT         2   // Right Front
#define   LED_LEFT_FRONT          3   // Left Front

// ==== [ Color Values ] ======================================================
const int RED[]                 = {255, 0, 0};
const int GREEN[]               = {0, 255, 0};
const int BLUE[]                = {0, 0, 255};
const int ORANGE[]              = {255, 80, 0};
const int WHITE[]               = {255, 255, 255};

// ==== [ Infrared Sensors ] ==================================================
const int IR_SENSORS[]          = {A3, A2, A1, A0}; // From left to right when looking from the back, sensor 1, 3, 6, 8

// ==== [ Wheelcontrol counters]  =============================================
long pulsesLeft                 = 0;
long pulsesRight                = 0;
long stuckTimer                 = 0;
long turnTimer                  = 0;

// ==== [ Speaker pin ] =======================================================
#define BUZZER                    13  // Speaker was A5

enum Direction {forward, right, left, backwards, none};
enum Action {drivingForward, turningLeft, turningRight, turningRight2, unstuckBoth, unstuckLeft, unstuckRight};
enum IsStuck {stuckLeft, stuckRight, stuckBoth, notStuck};
IsStuck isCurrentlyStuck;
Direction driveDirection;
Action currentAction;
unsigned long timeToStartDetectingFinish;

void setup()
{
  Serial.begin(9600);

  // Motor
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR_LEFT_READ), incrementPulseLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR_RIGHT_READ), incrementPulseRight, CHANGE);

  // Echo Sensor
  pinMode(ECHO_FORWARD[0], INPUT);
  pinMode(ECHO_FORWARD[1], OUTPUT);
  pinMode(ECHO_LEFT[0], INPUT);
  pinMode(ECHO_LEFT[1], OUTPUT);

  // IR Sensoren
  for(int element : IR_SENSORS)
  {
    pinMode(element, INPUT);
  }

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // Color setup
  strip.begin();
  setPixelRgb(LED_LEFT_FRONT, 255, 255, 255);
  setPixelRgb(LED_RIGHT_FRONT, 255, 255, 255);
  setPixelRgb(LED_LEFT_BACK, 128, 0, 0);
  setPixelRgb(LED_RIGHT_BACK, 128, 0, 0);
  
  startup();
  isCurrentlyStuck = notStuck;
  currentAction = drivingForward;
}

void loop()
{
//  Play Doom soundtrack when entering the maze
  //playDoom();
  //readIrOutput();
  gripperUpdate();
  switch(currentAction)
  {
    case drivingForward: 
      if(detectWall(ECHO_FORWARD, STOP_DISTANCE))
      {
        currentAction = turningRight;
      }
      if(!detectWall(ECHO_LEFT, WALLHUG_DISTANCE + 5))
      {
        driveDirection = left;
        setMotors(0, 0, DRIVE_SPEED, 0); 
      }
      else if(detectWall(ECHO_LEFT, WALLHUG_DISTANCE + 1))
      {
        setMotors(DRIVE_SPEED, 0, DRIVE_SPEED - 100, 0);
      }
      else if(ECHO_LEFT, WALLHUG_DISTANCE - 1)
      {
        setMotors(DRIVE_SPEED - 100, 0, DRIVE_SPEED, 0); 
      }
      else
      {
        driveForward(255);
      }
      break;
    case turningRight:
      driveDirection = right;
      if(!detectWall(ECHO_FORWARD, STOP_DISTANCE + 10))
      {
        turnTimer = millis() + 150;
        currentAction = turningRight2;
      }
      else
      {
        turnRightSlow();  
      }
      break;
    case turningRight2:
      if (turnTimer > millis())
      {
        driveRight(255);
      }
      else
      {
        currentAction = drivingForward;
      }
      break;
    case unstuckBoth:
      driveDirection = backwards;
      driveBack(255);
      if (stuckTimer < millis())
      {
        currentAction = drivingForward;
      }
      break;
    case unstuckLeft:
      driveDirection = backwards;
      turnRightBack();
      if (stuckTimer < millis())
      {
        currentAction = drivingForward;
      }
      break;
    case unstuckRight:
      turnLeftBack();
      driveDirection = backwards;
      if (stuckTimer < millis())
      {
        currentAction = drivingForward;
      }
      break;
    default:
      currentAction = drivingForward;
  }
  
  switch(driveDirection)
  {
    case left:
      blinkLed(LED_LEFT_FRONT);
      break;
    case right:
      blinkLed(LED_RIGHT_FRONT);
      break;
    case backwards:
      setPixelByName(LED_RIGHT_BACK, WHITE);
    default:
      blinkLed(100);
      setPixelByName(LED_RIGHT_BACK, RED);
      break;
  }

  if (timeToStartDetectingFinish < millis())
  {
    detectFinish();
  }
  isStuck();
  switch (isCurrentlyStuck)
  {
    case stuckBoth:
      isCurrentlyStuck = notStuck;
      currentAction = unstuckBoth;
      stuckTimer = millis() + 500;
      break;
    case stuckLeft:
      isCurrentlyStuck = notStuck;
      currentAction = unstuckLeft;
      stuckTimer = millis() + 500;
      break;
    case stuckRight:
      isCurrentlyStuck = notStuck;
      stuckTimer = millis() + 500;
      break;
    case notStuck:
    default:
      isCurrentlyStuck = notStuck;
      break;
  }
}

void stayOnLine(int speed)
{
  if (!isLightOnLeft())
  {
    setMotors(speed, 0, 0, 0);
  }
  else if(!isLightOnRight())
  {
    setMotors(0, 0, speed, 0);
  }
  else
  {
    driveForward(speed);
  }
}

void startup()
{
  int linesPassed = 0;
  int amountOfPulses = 0;
  boolean currentColor = false;
  boolean hasGotPion = false;
  boolean detectedPion = false;

  // Wait untill an object is detected in front of it
  if (linesPassed == 0)
  {
     gripperOpen();
     while(!playNokia())
     {
       gripperUpdate();
     }
     while(!detectedPion)
     {
        Serial.println("Waiting for start signal");
        if (!detectWall(ECHO_FORWARD, 30))
        {
          amountOfPulses = 0;
        }
        else
        {
          amountOfPulses++;
        }
        if (amountOfPulses >= 10)
        {
          detectedPion = true;
        } 
     } 
     delay(1000);
  }
  driveForward(255);
  //Count the lines it passes whilst driving forward
  //When it reaches 7 switches, go to the next phase
  while(linesPassed <= 6)
  {
    boolean detectedColor = isOnLightColor();
    if (currentColor != detectedColor)
    {
      currentColor = detectedColor;
      linesPassed++;
    }
  }
  //Loop untill it's done with the startup sequence
  while(true)
  {
    //Close the gripper once a black line is detected
    if (!isOnLightColor())
    {
      gripperClose();
      hasGotPion = true;
    }
    gripperUpdate();
    //If it has the Pion, drive forward untill it reached the end of the black square
    if (hasGotPion)
    {
      if (isOnLightColor())
      {
        //Stuff to follow the line for a small bit
        driveLeft(255);
        delay(500);
        long timer = millis() + 1500;
        while(timer > millis())
        {
          Serial.println("Staying on line");
          stayOnLine(200);
        }
        driveForward(200);
        break;
      }
    }
  }
  timeToStartDetectingFinish = millis() + 10000;
}

void detectFinish()
{
  if(isAnythingBlack())
  {
    Serial.println("Running Finish");
    while(isOnLightColor())
    {
      stayOnLine(255);
    }  
    dropPion();
  }
}

void dropPion()
{
  gripperOpen();
  unsigned long timer = millis() + 1000; 
  while(timer > millis())
  {
    gripperUpdate();
    driveBack(255);
  }
  driveStop();
  while(!playFinalFantasy());
  while(true);
}
