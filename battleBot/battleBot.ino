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
#define   STOP_DISTANCE           15  // Distance threshold to stop the robot (in cm)
#define   WALLHUG_DISTANCE        10  // Distance from the left wall


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
enum Action {drivingForward, turningBack, unstuck};
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
  lsm6ds3trc.setGyroRange(LSM6DS_GYRO_RANGE_125_DPS);
  Serial.print("Gyro range set to: ");
  switch (lsm6ds3trc.getGyroRange()) {
    case LSM6DS_GYRO_RANGE_125_DPS: Serial.println("125 degrees/s"); break;
    case LSM6DS_GYRO_RANGE_250_DPS: Serial.println("250 degrees/s"); break;
    case LSM6DS_GYRO_RANGE_500_DPS: Serial.println("500 degrees/s"); break;
    case LSM6DS_GYRO_RANGE_1000_DPS: Serial.println("1000 degrees/s"); break;
    case LSM6DS_GYRO_RANGE_2000_DPS: Serial.println("2000 degrees/s"); break;
  }
  echoSensorForward();
  gripperClose();
  currentAction = checkingForward;
  
  Serial.println("Finished");
}

// Await signal
// Grab object
// Enter maze
void loop()
{
  //init timer
  static long timer = millis() + 400;
  // DO NOT REMOVE
  updateRotation();
  gripperUpdate();
  //TODO make the thingy wait before it is fully rotated

//  switch(currentAction)
//  {
//    case drivingForward: 
//    case turningBack:
//    case unstuck:
//  }

  
  /*
  switch(currentAction)
  {
    case drivingForward: // Drive forward and check the left side
      Serial.println("Driving forward");
      driveForward(255);
      echoSensorLeft();
      if (hasReachedWall())
      {
        currentAction = checkingForward;
      }
      if (!detectWall() && millis() >= timer)
      {
        currentAction = turningLeft;
      }
            // Bereik je de muur: currentAction = checkingForward;
            // Gat in linker muur: currentAction = turningLeft;
      break;
    case checkingForward: // Check if the car can still drive forward more
      Serial.println("Checking forward");
      echoSensorForward();
      delay(400);
      if (!checkFrontWall())
      {
        setNewNextWall();
        currentAction = drivingForward;
        timer = millis() + 400;
      }
      else
      {
        driveStop();
        currentAction = checkingLeft; 
      }
        // Kan vooruit: currentAction = drivingForward;
        // Anders: CheckingLeft
      break;
    case checkingLeft: // Check if the car can go left
      Serial.println("Checking left");
      driveStop();
      if(!checkLeftWall())
      {
        currentAction = turningLeft;
      }
        // Check links
          // Kan links: currentAction = turningLeft;
          // Anders: currentAction = checkingRight;
      break;
    case checkingRight: // Check if the car can go right
      Serial.println("Checking right");
      driveStop();
      if(!checkRightWall())
      {
        currentAction = turningRight;
      }
      else
      {
        currentAction = turningBack;
      }
        // Check rechts
          // Kan rechts: currentAction = turningRight;
          // Anders: currentAction = turningBack;
      break;
    case turningLeft: // Turn left
      Serial.println("Turning left");
      if(turnLeft())
      {
        currentAction = checkingForward;  
      }
      break;
    case turningBack: // Turn around
      Serial.println("Turning back");
      if(turnBack())
      {
        currentAction = checkingForward;  
      }
      break;
    case turningRight:  // Turn right
      Serial.println("Turning right");
      if(turnRight())
      {
        currentAction = checkingForward;
      }
      break;
    default:
      currentAction = checkingForward;
      break;
  }
  
//  switch(driveDirection)
//  {
//    case left:
//      blinkLed(LED_LEFT_FRONT);
//      break;
//    case right:
//      blinkLed(LED_RIGHT_FRONT);
//      break;
//    default:
//      blinkLed(100);
//      break;
//  }
  */
}

// ==== [ Check for walls ] ===================================================
void setNewNextWall()
{
  long turnTime = millis() + 400;
  echoSensorForward();
  while (turnTime <= millis())
  {
    echoSensorUpdate();
  }
  distanceFromNextWall = distanceFromObject();
}

boolean hasReachedWall()
{
  if((pulsesToCentimeters((pulsesLeft - pulseOffset)) + 5) >= distanceFromNextWall)
  {
    pulseOffset = pulsesLeft;
    currentAction = checkingForward;
    return true;
  }
  return false;
}

// ==== [ Look arround functions ] ============================================
boolean checkLeftWall()
{
  long turnTime = millis() + 400;
  echoSensorLeft();
  while (turnTime <= millis())
  {
    echoSensorUpdate();
  }
  if (detectWall())
  {
    return true;
  }
  return false;
}

boolean checkRightWall()
{
  long turnTime = millis() + 400;
  echoSensorRight();
  while (turnTime <= millis())
  {
    echoSensorUpdate();
  }
  if (detectWall())
  {
    return true;
  }
  return false;
}

boolean checkFrontWall()
{
  long turnTime = millis() + 400;
  echoSensorForward();
  while (turnTime <= millis())
  {
    echoSensorUpdate();
  }
  if (detectWall())
  {
    return true;
  }
  return false;
}
