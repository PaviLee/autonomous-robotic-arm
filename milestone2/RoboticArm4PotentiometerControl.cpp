// For Platform.io, must import Arduino and Servo libraries. 
// If using Arduino IDE, only need to import Servo library.
#include <Arduino.h>
#include <Servo.h>

// Analog input pins for potentiometers.
#define POTA A0 // For servoA.
#define POTB A1 // For servoB.
#define POTC A2 // For servoC.
#define POTD A3 // For servoD.

// Create servo objects.
Servo servoA; // Arm Servo: Moves arm forwards and backwards.
Servo servoB; // Base Servo: Moves entire arm left and right.
Servo servoC; // Arm Servo: Moves arm up and down.
Servo servoD; // Claw Servo: Open and closes the claw.

void setup() {
  // Set potentiometer pins to INPUT mode to receive 
  // analog values.
  pinMode(POTA, INPUT);
  pinMode(POTB, INPUT);
  pinMode(POTC, INPUT);
  pinMode(POTD, INPUT);

  // Servos attached to corresponding PWM pins.
  servoA.attach(9);
  servoB.attach(6);
  servoC.attach(5);
  servoD.attach(3);
}

void loop() {
  // Read value from potentiomter. Servos can only take 
  // value from 0 to 180 degrees, so must map analog
  // range 0 to 1023 to range 0 to 180.
  int stateA = map(analogRead(POTA), 0, 1023, 0, 180);
  int stateB = map(analogRead(POTB), 0, 1023, 0, 180);
  int stateC = map(analogRead(POTC), 0, 1023, 90, 180); // Arm movement for servoC limited to 90+ degrees due to arm construction.
  int stateD = map(analogRead(POTD), 0, 1023, 90, 180); // Arm movement for servoD limited to 90+ degrees due to arm construction.

  // Write mapped potentiometer values to corresponding servos.
  servoA.write(stateA);
  servoB.write(stateB);
  servoC.write(stateC);
  servoD.write(stateD);

  // No need to loop over loop() so fast. Delay slows it down.
  delay(50);
}
