//Take a reading from an Ultrasonic sensor and post it to Adafruit.IO



// edit the config.h tab and enter your Adafruit IO credentials

#include "config.h"
#include <NewPing.h>    //requires the New Ping library

#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.




int sensorVal;          //variable to hold the value from the sensor


int sendRate = 700;     //rate that values are sent to adafruit.IO
int lastSend;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


// set up the 'distVal' feed
AdafruitIO_Feed *distVal = io.feed("distVal");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
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

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  //read sensor value
  sensorVal = sonar.ping_cm();

  if(millis()-lastSend>=sendRate)
  {
  // save randVal to the 'myRandoVal' feed on Adafruit IO
  distVal->save(sensorVal);
  
  //print the value to the serial monitor so you can check if its working
  Serial.print("sending -> ");
  Serial.println(sensorVal);
  
  lastSend = millis();
  }
}
