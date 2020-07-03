// For Platform.io, must import Arduino, Servo, and NewPing libraries.
// If using Arduino IDE, only need to import Servo and NewPing libraries.
#include <Arduino.h>
#include <Servo.h>
#include <NewPing.h>

// Constants for HC-SR04.
#define TRIGGER_PIN 11 // Input pin for HC-SR04
#define ECHO_PIN 12    // Output pin for HC-SR04
#define MIN_DIST 3     // Closest distance the arm can reach
#define MAX_DIST 12    // Farthest distance the arm can reach

// Create servo objects.
Servo servoA; // Arm Servo: Moves arm forwards and backwards.
Servo servoB; // Base Servo: Moves entire arm left and right.
Servo servoC; // Arm Servo: Moves arm up and down.
Servo servoD; // Claw Servo: Open and closes the claw.

// Create NewPing object.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);
int distance; // Used in loop().
int angleA, angleC;

// Angles for servoA and servoC.
int tableA[10] = {118, 132, 126, 134, 131, 144, 156, 156, 179, 179}; // <distance, angleA>
int tableC[10] = {139, 124, 148, 139, 157, 164, 168, 168, 180, 180}; // <distance, angleC>

void resetArm()
{
  // Arm resting position.
  servoA.write(90);
  servoB.write(90);
  servoC.write(180);
  servoD.write(90);
}

void setup()
{
  // Servos attached to corresponding PWM pins.
  servoA.attach(9);
  servoB.attach(6);
  servoC.attach(5);
  servoD.attach(3);

  resetArm();
}

void grabItem()
{
  servoD.write(180);
  delay(1000);
  servoA.write(angleA);
  delay(1000);
  servoC.write(angleC);
  delay(1000);
  servoD.write(110);
  delay(1000);
}

void dropItem()
{
  servoB.write(180);
  delay(1000);
  servoD.write(180);
  delay(1000);
}

void loop()
{
  distance = sonar.ping_cm(); //TODO implement mode/median

  if (distance < MIN_DIST || distance > MAX_DIST)
  {
    return; // Outside of arm reach range, quit loop for this iteration.
  }

  distance -= 3; // Transpose distance value to array index value.

  angleA = tableA[distance]; // Get angle data from array.
  angleC = tableC[distance]; // Get angle data from array.

  grabItem(); // Grabs item.

  resetArm(); // Brings arm back to resting position.
  delay(1000);

  dropItem(); // Drops item to left of arm.
  resetArm(); // Brings arm back to resting position.
}
