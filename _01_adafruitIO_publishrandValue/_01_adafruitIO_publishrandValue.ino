//Basic adafruitIO example
//post a random value every second



// edit the config.h tab and enter your Adafruit IO credentials

#include "config.h"




int randVal;


int sendRate = 1000;
int lastSend;



// set up the 'myRandoVal' feed
// channel name can be renamed
AdafruitIO_Feed *myRandoVal = io.feed("myRandoVal");

void setup() {

  // start the serial connection to see what's happening
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com account
  io.connect();

  // wait for a connection if not connected it displays a dot
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run();...
  // ...is required for all sketches and stays on top because it holds everything and keeps it going. keeps connection
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  //pick a random number
  randVal = random(10,100);

  //need to limit amount of data often sent
  
  if(millis()-lastSend>=sendRate)
  {
  // save randVal to the 'myRandoVal' feed on Adafruit IO
  myRandoVal->save(randVal);
  
  //print the value to the serial monitor so you can check if its working
  Serial.print("sending -> ");
  Serial.println(randVal);
  
  lastSend = millis();
  }
}
