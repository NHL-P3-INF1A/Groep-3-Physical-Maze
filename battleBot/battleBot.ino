// Neopixel Setup
#include <Adafruit_NeoPixel.h>

// Motor Pins
const int motorLeftBack =   12;  // Motor A1 LB
const int motorLeftFwd =    11;  // Motor A2 LF
const int motorRightFwd =   10;  // Motor B1 RF
const int motorRightBack =  6;   // Motor B2 RB

const int motorLeftRead =   8;   // Arduino A0
const int motorRightRead =  7;   // Arduino A1

// Echo Sensor Pins
const int echoServo = 5;
const int echoPinRead = 9; // Echo 
const int echoPinSend = 4; // Trigger 
const int stopDistance = 10; // Distance threshold to stop the robot (in cm)

// Gripper Pins
const int gripperServo = 3;

//LED
const int LED_PIN = 2;
const int LED_COUNT = 4;
const int brightness = 125;

//Led Layout
const int LB = 0;   //Left Back
const int RB = 1;   //Right Back
const int RF = 2;   //Right Front
const int LF = 3;   //Left Front

//Color Values
const int RED[] = {255, 0, 0};
const int GREEN[] = {0, 255, 0};
const int BLUE[] = {0, 0, 255};
const int ORANGE[] = {255, 80, 0};

//Infrared sensoren 
const int IrSensors[] = {A0, A1, A2, A3, A4, A5, A6, A7};

enum Direction {forward, right, left, backwards, none};
Direction driveDirection;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup() 
{
  // Motor
  pinMode(motorLeftFwd,   OUTPUT);
  pinMode(motorLeftBack,  OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  pinMode(motorRightFwd,  OUTPUT);
  pinMode(motorLeftRead,  INPUT);
  pinMode(motorRightRead, INPUT);
  // Echo Sensor
  pinMode(echoPinRead, INPUT);
  pinMode(echoPinSend, OUTPUT);
  // ir Sensoren
  for(int element : IrSensors)
  {
    pinMode(element, INPUT);
  }
  Serial.begin(9600);
  // calibrate();
  // driveForward(255);
  //
  //Color setup
  strip.begin();
  setPixelRgb(LF, 255, 255, 255);
  setPixelRgb(RF, 255, 255, 255);
  setPixelRgb(LB, 128, 0, 0);
  setPixelRgb(RB, 128, 0, 0);
  //
}

void loop() 
{
//  for (int element : IrSensors)
//  {
//    Serial.print(analogRead(element));
//    Serial.print(" ");
//  }
//  Serial.println();

  // Await signal
  // Grab object
  // Enter maze

  // Solve Maze
    // Drive forward
    // Detect wall
      // Stop
      // Check wall left
        // if WALL
          // Check wall right
            // if WALL
              // turnBack 
              // driveForward
            // else
              // turnRight
              // driveForward
        // else
          // turnLeft
          // driveForward
        
    if(detectWall())
    {
      driveStop();
      echoSensorLeft();
      if(detectWall())
      {
        echoSensorRight();
        if(detectWall())
        {
          turnBack();
        }
        else
        {
          turnRight();
        }
      }
      else
      {
        turnLeft();
      }
    }
    else
    {
      echoSensorForward();
      driveForward(255);  
    }
  
//  switch(driveDirection)
//  {
//    case left: 
//      blink(LF);
//      break;
//    case right:
//      blink(RF);
//      break;
//    default:
//      blink(100);
//      break;
//  }
  // showPulses();
}
