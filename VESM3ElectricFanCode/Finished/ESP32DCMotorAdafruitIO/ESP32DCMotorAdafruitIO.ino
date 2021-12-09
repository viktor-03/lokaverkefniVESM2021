#include <analogWrite.h>
#include "Config.h"

#define PIN_IN1 26
#define PIN_IN2 27
#define PIN_ENA 14

int current = 0;
int last = -1;
AdafruitIO_Feed *analog = io.feed("fan-project.temperature");


void setup() {
   pinMode(PIN_IN1, OUTPUT);
   pinMode(PIN_IN2, OUTPUT);
   pinMode(PIN_ENA, OUTPUT);

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
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
}

void handleMessage(AdafruitIO_Data *data)
{
  int temp = data->toInt();
  Serial.println(temp);
  if(temp != last)
  {
    if(temp <= 21)
    {
      Serial.println("OFF");
      analogWrite(PIN_ENA, 0);
    }
    else if(temp >= 26)
    {
      Serial.println("140");
      analogWrite(PIN_ENA, 140);
    }
    else if(temp > 24 && temp < 26)
    {
      Serial.println("110");
      analogWrite(PIN_ENA, 110);
    }
    else if(temp > 21 && temp < 24)
    {
      Serial.println("80");
      analogWrite(PIN_ENA, 80);
    }
    last = temp;
  }
}
