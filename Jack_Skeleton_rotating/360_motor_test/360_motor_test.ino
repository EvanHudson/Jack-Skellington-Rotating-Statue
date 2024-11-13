#include <Servo.h>

// Create a servo object
Servo myMotor;

void setup() {
  // Attach the servo on pin 9 to the servo object
  myMotor.attach(9);
}

void loop() {
  // Rotate the motor slowly in one direction
  myMotor.write(100);   // Slightly above neutral (try 100 to 180)
  delay(3000);          // Wait for 3 seconds

  // Stop the motor
  myMotor.write(90);    // Neutral position to stop the motor
  delay(2000);          // Wait for 2 seconds

  // Rotate the motor slowly in the opposite direction
  myMotor.write(80);    // Slightly below neutral (try 80 to 0)
  delay(3000);          // Wait for 3 seconds

  // Stop the motor again
  myMotor.write(90);    // Stop the motor
  delay(2000);          // Wait for 2 seconds
}
