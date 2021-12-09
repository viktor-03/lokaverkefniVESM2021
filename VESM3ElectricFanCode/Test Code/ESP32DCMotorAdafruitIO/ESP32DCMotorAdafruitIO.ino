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
bool upp = 0;
int stefna = 0;

int current = 0;
int last = 0;
AdafruitIO_Feed *analog = io.feed("fan-project.fanspeed");
AdafruitIO_Feed *rotate = io.feed("fan-project.fanmovement");

void setup() {
   pinMode(motorPin, OUTPUT);
   myservo.attach(13);
   Serial.begin(9600);
   while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  analog->onMessage(handleMessage);
  rotate->onMessage(handleRotate);

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
  
  
  if(fanRotate == true)
  {
    if(upp)
    {
      stefna++;
    }
    else
    {
      stefna--;
    }
    if(stefna > 180 || stefna < 0)
    {
      upp = !upp;
    }
    myservo.write(stefna);
  }
}

void handleMessage(AdafruitIO_Data *data)
{
  int reading = data->toInt();
  Serial.println(reading);
  current = reading;
  if(current != last)
  {
    if(int(reading) == 0)
    {
      Serial.println("OFF");
      analogWrite(motorPin, LOW);
    }
    else if(int(reading) == 1)
    {
      Serial.println("80");
      analogWrite(motorPin, 80);
    }
    else if(int(reading) == 2)
    {
      Serial.println("150");
      analogWrite(motorPin, 150);
    }
    else if(int(reading) == 3)
    {
      Serial.println("200");
      analogWrite(motorPin, 200);
    }
  }
  last = current;
}

void handleRotate(AdafruitIO_Data *data)
{
  String readTurn = data->toString();
  Serial.print("Rotation: ");
  Serial.println(readTurn);
  stepMove = readTurn;

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
}
