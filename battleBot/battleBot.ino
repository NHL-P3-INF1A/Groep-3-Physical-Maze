// ==== [ Neopixel Setup ] ====================================================
#include <Adafruit_NeoPixel.h>

// ==== [ Motor Pins ] ========================================================
#define   MOTOR_LEFT_BACK         12  // Motor A1 LB
#define   MOTOR_LEFT_FORWARD      11  // Motor A2 LF
#define   MOTOR_RIGHT_FORWARD     10  // Motor B1 RF
#define   MOTOR_RIGHT_BACK        6   // Motor B2 RB

#define   MOTOR_LEFT_READ         3   // Interrupt Left motor
#define   MOTOR_RIGHT_READ        2   // Interrupt Right motor

// ==== [ Echo Sensor Pins ] ==================================================
#define   ECHO_SERVO              5
#define   ECHO_READ               9   // Echo 
#define   ECHO_SEND               4   // Trigger 
#define   STOP_DISTANCE           10  // Distance threshold to stop the robot (in cm)


// ==== [ Gripper Pins ] ======================================================
#define   GRIPPER_SERVO           7

// ==== [ LED ] ===============================================================
#define   LED_PIN                 8
#define   LED_COUNT               4
#define   BRIGHTNESS              125

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

// ==== [ Infrared Sensoren ] =================================================
const int IR_SENSORS[]          = {A7, A6, A5, A4, A3, A2, A1, A0}; // From left to right when looking from the back

// ==== [ Array for IrSensor ] ================================================
int sensorTresholds[8][2];
bool sensorColor[8];

enum Direction {forward, right, left, backwards, none};
Direction driveDirection;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

int pulsesLeft = 0;
int pulsesRight = 0;

void setup() 
{
  // Motor
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR_LEFT_READ), incrementPulseLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR_RIGHT_READ), incrementPulseRight, CHANGE);
  // Echo Sensor
  pinMode(ECHO_READ, INPUT);
  pinMode(ECHO_SEND, OUTPUT);
  // ir Sensoren
  for(int element : IR_SENSORS)
  {
    pinMode(element, INPUT);
  }
  Serial.begin(9600);
  //Color setup
  strip.begin();
  setPixelRgb(LED_LEFT_FRONT, 255, 255, 255);
  setPixelRgb(LED_RIGHT_FRONT, 255, 255, 255);
  setPixelRgb(LED_LEFT_BACK, 128, 0, 0);
  setPixelRgb(LED_RIGHT_BACK, 128, 0, 0);
  //
}

void loop() 
{
  // Await signal
  // Grab object
  // Enter maze

  readIrOutput();

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
