#include <analogWrite.h>
#include "Config.h"

int motorPin = 2;

int current = 0;
int last = -1;
AdafruitIO_Feed *analog = io.feed("fan-project.temperature");


void setup() {
   pinMode(motorPin, OUTPUT);

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
}

void handleMessage(AdafruitIO_Data *data)
{
  int temp = data->toInt();
  Serial.println(temp);
  if(temp != last)
  {
    if(temp <= 20)
    {
      Serial.println("OFF");
      analogWrite(motorPin, 0);
    }
    else if(temp >= 26)
    {
      Serial.println("200");
      analogWrite(motorPin, 80);
    }
    else if(temp >= 24)
    {
      Serial.println("150");
      analogWrite(motorPin, 150);
    }
    else if(temp >= 21)
    {
      Serial.println("80");
      analogWrite(motorPin, 200);
    }
    last = temp;
  }
}
