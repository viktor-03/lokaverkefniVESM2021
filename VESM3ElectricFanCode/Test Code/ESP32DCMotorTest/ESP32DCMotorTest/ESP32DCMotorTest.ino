#include <analogWrite.h>

/*
  TB6612FNG H-Bridge Demo
  TB6612-Demo.ino
  Demonstrates use of TB6612FNG H-Bridge Motor Controller
  Drives two DC Motors

  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Motor B

int stdByPin = 12;
int pwmB = 25;
int in1B = 27;
int in2B = 26;

void setup()

{

  // Set all the motor control pins to outputs

  pinMode(pwmB, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);
}

void loop() {

 // Set Motor B forward
  digitalWrite(stdByPin, HIGH);
  digitalWrite(in1B, HIGH);
  digitalWrite(in2B, LOW);

  analogWrite(pwmB, 100);
  
}
