// ==== [ Neopixel Setup ] ====================================================
#include <Adafruit_NeoPixel.h>

// ==== [ Motor Pins ] ========================================================
const int motorLeftBack =   12;  // Motor A1 LB
const int motorLeftFwd =    11;  // Motor A2 LF
const int motorRightFwd =   10;  // Motor B1 RF
const int motorRightBack =  6;   // Motor B2 RB

const int motorLeftRead =   3;   // Interrupt Left motor
const int motorRightRead =  2;   // Interrupt Right motor

// ==== [ Echo Sensor Pins ] ==================================================
const int echoServo = 5;
const int echoPinRead = 9;    // Echo 
const int echoPinSend = 4;    // Trigger 
const int stopDistance = 10;  // Distance threshold to stop the robot (in cm)


// ==== [ Gripper Pins ] ======================================================
const int gripperServo = 7;

// ==== [ LED ] ===============================================================
const int LED_PIN = 8;
const int LED_COUNT = 4;
const int brightness = 125;

// ==== [ Led Layout ] ========================================================
const int ledLeftBack = 0;      //Left Back
const int ledRightBack = 1;     //Right Back
const int ledRightFront = 2;    //Right Front
const int ledLeftFront = 3;     //Left Front

// ==== [ Color Values ] ======================================================
const int RED[] = {255, 0, 0};
const int GREEN[] = {0, 255, 0};
const int BLUE[] = {0, 0, 255};
const int ORANGE[] = {255, 80, 0};

// ==== [ Infrared Sensoren ] =================================================
const int IrSensors[] = {A7, A6, A5, A4, A3, A2, A1, A0}; // From left to right when looking from the back

// ==== [ Array for IrSensor ] ================================================
int sensorOffsets[8];

enum Direction {forward, right, left, backwards, none};
Direction driveDirection;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

int pulsesLeft = 0;
int pulsesRight = 0;

void setup() 
{
  // Motor
  pinMode(motorLeftFwd, OUTPUT);
  pinMode(motorLeftBack, OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  pinMode(motorRightFwd, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motorLeftRead), incrementPulseLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motorRightRead), incrementPulseRight, CHANGE);
  // Echo Sensor
  pinMode(echoPinRead, INPUT);
  pinMode(echoPinSend, OUTPUT);
  // ir Sensoren
  for(int element : IrSensors)
  {
    pinMode(element, INPUT);
  }
  Serial.begin(9600);
  //Color setup
  strip.begin();
  setPixelRgb(ledLeftFront, 255, 255, 255);
  setPixelRgb(ledRightFront, 255, 255, 255);
  setPixelRgb(ledLeftBack, 128, 0, 0);
  setPixelRgb(ledRightBack, 128, 0, 0);
  //

  calibrateIrSensors(1000);
}

void loop() 
{
  // Await signal
  // Grab object
  // Enter maze

  blink(ledRightFront);

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
        
    // if(detectWall())
    // {
    //   driveStop();
    //   echoSensorLeft();
    //   if(detectWall())
    //   {
    //     echoSensorRight();
    //     if(detectWall())
    //     {
    //       turnBack();
    //     }
    //     else
    //     {
    //       turnRight();
    //     }
    //   }
    //   else
    //   {
    //     turnLeft();
    //   }
    // }
    // else
    // {
    //   echoSensorForward();
    //   driveForward(255);  
    // }
  
//  switch(driveDirection)
//  {
//    case left: 
//      blink(ledLeftFront);
//      break;
//    case right:
//      blink(ledRightFront);
//      break;
//    default:
//      blink(100);
//      break;
//  }

  // Serial.print("Left pulses = ");
  // Serial.print(pulsesLeft);
  // Serial.print(" | Right pulses = ");
  // Serial.print(pulsesRight);
  // Serial.println();
}
