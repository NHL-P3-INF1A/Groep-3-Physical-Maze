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
const int echoPinRead = A0; // Echo 
const int echoPinSend = A1; // Trigger 
const int stopDistance = 10; // Distance threshold to stop the robot (in cm)

// Gripper Pins
const int gripperServo = 3;

//LED
const int LED_PIN = 2;
const int LED_COUNT = 4;
const int brightness = 125;

const int totalBlinks = 3;

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

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
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
  // 
  Serial.begin(9600);
  calibrate();
  driveForward(255);
  //
  //Color setup
  strip.begin();
  setPixelRgb(LB, 255, 0, 0);
  setPixelRgb(RB, 255, 0, 0);
  setPixelRgb(RF, 255, 255, 255);
  setPixelRgb(LF, 255, 255, 255);
  //
}

void loop() {
   addPulses(1000, true, true);
}
