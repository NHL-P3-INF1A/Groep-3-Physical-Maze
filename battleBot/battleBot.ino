// ==== [ Neopixel Setup ] ====================================================
#include <Adafruit_NeoPixel.h>
#define   LED_PIN                 8   // Pin that the neopixels are connected to
#define   LED_COUNT               4   // Amount of LEDs
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

// ==== [ Gyroscope Setup] ====================================================
#include <Adafruit_LSM6DS3TRC.h>
Adafruit_LSM6DS3TRC lsm6ds3trc;
#define PI 3.1415926535897932384626433832795 // Value of Pi
double rotationInDegrees;

// ==== [ Motor Pins ] ========================================================
#define   MOTOR_LEFT_BACK         12  // Motor A1 LB
#define   MOTOR_LEFT_FORWARD      11  // Motor A2 LF
#define   MOTOR_RIGHT_FORWARD     10  // Motor B1 RF
#define   MOTOR_RIGHT_BACK        6   // Motor B2 RB

#define   MOTOR_LEFT_READ         3   // Interrupt Left motor
#define   MOTOR_RIGHT_READ        2   // Interrupt Right motor

// ==== [ Echo Sensor Pins ] ==================================================
#define   ECHO_SERVO              5   // Servo for echo sensor rotation
#define   ECHO_READ               9   // Echo
#define   ECHO_SEND               4   // Trigger
#define   STOP_DISTANCE           10  // Distance threshold to stop the robot (in cm)
double    distanceFromNextWall  = null;


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
int pulsesLeft                  = 0;
int pulsesRight                 = 0;

enum Direction {forward, right, left, backwards, none};
Direction driveDirection;

void setup()
{
  Serial.begin(115200);

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

  // Check if gyro sensor chip works
  if (!lsm6ds3trc.begin_I2C())
  {
    Serial.println("Failed to find LSM6DS3TR-C chip");
  }
  lsm6ds3trc.configInt1(false, false, true); // accelerometer DRDY on INT1
  lsm6ds3trc.configInt2(false, true, false); // gyro DRDY on INT2
}

// Await signal
// Grab object
// Enter maze
void loop()
{
  blinkLed(LED_LEFT_FRONT);
//  Serial.println(rotationInDegrees);
//  updateRotation();
//  readIrOutput();

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
}
