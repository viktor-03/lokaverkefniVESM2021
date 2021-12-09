#include <analogWrite.h>
#include "Config.h"
#include "DHT.h"

AdafruitIO_Feed *analog = io.feed("fan-project.temperature");
double temp = 0;
double last = 0;
int DHT11PIN = 2;

DHT dht(DHT11PIN, DHT11);

void setup() {
  dht.begin();
   Serial.begin(9600);
   while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

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
  temp = dht.readTemperature();
  Serial.println(temp);
  if(temp != last)
  {
    analog -> save(temp);
    Serial.println("Uploading to adafruit...");
  }
  else
  {
    Serial.println("Temperature has not changed...");
  }
  last = temp;
  delay(5000);
}
