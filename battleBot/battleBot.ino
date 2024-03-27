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

// ==== [ Echo Sensor Pins ] ==================================================
const int ECHO_FORWARD[]        = {9, 4}; // {Echo Read, Echo Send}
const int ECHO_LEFT[]           = {5, 13};
#define   STOP_DISTANCE           10  // Distance threshold to stop the robot (in cm)
#define   WALLHUG_DISTANCE        8  // Distance from the left wall

// ==== [ Gripper Pins ] ======================================================
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

// ==== [ Infrared Sensoren ] =================================================
const int IR_SENSORS[]          = {A3, A2, A1, A0}; // From left to right when looking from the back, sensor 1, 3, 6, 8

// ==== [ Array for IrSensor ] ================================================
int sensorTresholds[4][2];
bool sensorColor[4];

// ==== [ Wheelcontrol counters]  =============================================
#define PI 3.1415926535897932384626433832795 // Value of Pi
long pulsesLeft                 = 0;
long pulsesRight                = 0;
long pulseOffset                = 0;

enum Direction {forward, right, left, backwards, none};
enum Action {drivingForward, turningRight, unstuck};
Direction driveDirection;
Action currentAction;

void setup()
{
  Serial.begin(9600);
 
  // Motor
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR_LEFT_READ), incrementPulseLeft, CHANGE);

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

  // Color setup
  strip.begin();
  setPixelRgb(LED_LEFT_FRONT, 255, 255, 255);
  setPixelRgb(LED_RIGHT_FRONT, 255, 255, 255);
  setPixelRgb(LED_LEFT_BACK, 128, 0, 0);
  setPixelRgb(LED_RIGHT_BACK, 128, 0, 0);
  
  gripperClose();
  currentAction = drivingForward;
}

// Await signal
// Grab object
// Enter maze
void loop()
{
  gripperUpdate();
//
 
  switch(currentAction)
  {
    case drivingForward: 
      if(detectWall(ECHO_FORWARD, STOP_DISTANCE))
      {
        currentAction = turningRight;
      }
      driveForward(255);
      break;
    case turningRight:
      if(!detectWall(ECHO_FORWARD, STOP_DISTANCE + 10))
      {
        driveStop();
        currentAction = drivingForward;
      }
      else
      {
        turnRight();  
      }
      break;
    case unstuck:
      // TODO: drive backwards when stuck
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
    default:
      blinkLed(100);
      break;
  }
}

boolean startup()
{
  int linesPassed = 0;
  boolean currentColor = false;
  boolean done = false;
  boolean hasGotPilon = false;

  if (linesPassed == 0)
  {
     while(!detectWall(ECHO_FORWARD, 59)){} 
     delay(1000);
  }
  driveForward(200);
  while(linesPassed <= 6)
  {
    if (currentColor != isOnLightColor())
    {
      currentColor = isOnLightColor;
      linesPassed++;
    }
  }
  while(!done)
  {
    if (!isOnLightColor())
    {
      gripperClose();
      hasGotPilon = true;
    }
    if (hasGotPilon)
    {
      if (isOnLightColor())
      {
        //Stuff to follow the line for a small bit
        turnLeft();
        done = true;
      }
    }
  }
}
