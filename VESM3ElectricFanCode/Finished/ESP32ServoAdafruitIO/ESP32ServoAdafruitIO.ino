#include <analogWrite.h>
#include "Config.h"
#include <Servo.h>

bool fanRotate = false;
int pos = 0;
Servo myservo;
bool upp = 0;
int stefna = 0;

AdafruitIO_Feed *analog = io.feed("fan-project.temperature");

void setup() {
   myservo.attach(13);
   Serial.begin(9600);
   while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  analog->onMessage(handleMessage);

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
      stefna+= 2;
    }
    else
    {
      stefna-= 2;
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
  int temp = data->toInt();
  Serial.println(temp);

  if(temp > 22)
  {
    fanRotate = true;
  }
  else
  {
    fanRotate = false;
  }
}
