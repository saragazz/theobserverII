//get the MAC address of your board so it can be added to the OCAD network


#include <ESP8266WiFi.h>

String theMAC;
String printMAC;
void setup()
{
 Serial.begin(115200); 
 String theMac = WiFi.macAddress();
 theMac.replace(":","-");
 Serial.println("****Your Mac address is below****");
 Serial.println(theMac);
}

void loop()
{

  
}



