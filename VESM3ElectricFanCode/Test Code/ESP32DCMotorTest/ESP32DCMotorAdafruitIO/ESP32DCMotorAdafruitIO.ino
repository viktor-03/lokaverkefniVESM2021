#include <analogWrite.h>
#include "Config.h"
#include <Servo.h>
int motorPin = 2;
int stepPin = 13;

String stepMove = "";
String stepLast = "";
bool fanRotate = false;
int pos = 0;
Servo myservo;

int current = -1;
int last = 0;
AdafruitIO_Feed *analog = io.feed("fan-project.fanspeed");
// AdafruitIO_Feed *rotate = io.feed("fan-project.fanmovement");

void setup() {
   pinMode(motorPin, OUTPUT);
   myservo.attach(13);
   Serial.begin(9600);
   while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  analog->onMessage(handleMessage);
  // rotate->onMessage(handleRotate);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
  /*
  Serial.print(fanRotate);
  if(fanRotate == true)
  {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);
  }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(30);
    }
  }*/
}

void handleMessage(AdafruitIO_Data *data)
{
  last = current;
  int reading = data->toInt();
  current = reading;
  while(current != 0)
  {
    if(current != last)
    {
      if(current == 1)
      {
        analogWrite(motorPin, 80);
      }
      else if(current == 2)
      {
        analogWrite(motorPin, 150);
      }
      else if(current == 3)
      {
        analogWrite(motorPin, 200);
      }
    }

    if(current == last)
    {
      for (pos = 0; pos <= 180; pos += 1)
      {
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(30);
      }
    }

    if(current == last)
    {
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
        delay(30);
      }
    }
  }
  last = current;
  reading = data->toInt();
  current = reading;
  if(current == 0)
  {
    analogWrite(motorPin, 0);
  }
}

/*void handleRotate(AdafruitIO_Data *data)
{
  String reading = data->toString();
  Serial.print("Rotation: ");
  Serial.println(reading);
  stepMove = reading;

  if(stepMove != stepLast)
  {
    if(stepMove == "OFF")
    {
      fanRotate = false;
    }
    else if(stepMove == "ON")
    {
      fanRotate = true;
    }
  }
  stepLast = stepMove;
  loop2();
}*/
