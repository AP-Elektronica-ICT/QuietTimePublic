#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9,10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

/**
 * User Configuration: nodeID - A unique identifier for each radio. Allows addressing
 * to change dynamically with physical changes to the mesh.
 *
 * In this example, configuration takes place below, prior to uploading the sketch to the device
 * A unique value from 1-255 must be configured for each node.
 * This will be stored in EEPROM on AVR devices, so remains persistent between further uploads, loss of power, etc.
 *
 **/
#define nodeID 2

unsigned int Mean = 0;   // peak-to-peak level 
unsigned int signalMax;        //aanmaken min en max signaalwaarde
unsigned int signalMin;
unsigned int sample = 0;       //variabele voor het inlezen van het signaal

uint32_t PrevTimer = 0;

void setup() {

  Serial.begin(115200); 
  
  // Set the nodeID manually each node must have a different ID
  mesh.setNodeID(nodeID);  
  
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin();
}


void loop() {

  mesh.update();

  // Send to the master node every 2 seconds
  if (millis() - PrevTimer >= 2000) {
    PrevTimer = millis(); //initiele tijd bijhouden zodat we kunnen zien wanneer er 5seconde over zijn

    
    signalMax = 0;
    signalMin = 1024;
    
    // collect data for 50 ms, zo hier kunnen we het gemiddelde tussen het max en min signaal berekenen. 
    // ipv misch toevallig net het maximum signaal uit te lezen en als volgt een vertekend beeld te krijgen. 
   while (millis() - PrevTimer < 50)
   {
      sample = analogRead(0);     //uitgangssignaal van de microfoon inlezen
      if (sample < 1024)          // verwijderen van fictieve signalen
      {
         if (sample > signalMax)      //initeel is elk signaal groter als signalmax(signalmax = 0). signalmax zal dus gelijk gesteld worden aan het eerste signaal. 
         {                            //is het Tweede signaal groter dan het eerste dan zal dit bewaard worden in signal max enz.
            signalMax = sample;       
         }
         else if (sample < signalMin) //is de sample niet groter als signal max gaan we kijken of hij kleiner is dan signalmin. dit is de eerste keer sowieso het geval. 
         {
            signalMin = sample;
         }
      }
   }
   
   Mean = (signalMax + signalMin)/2;                 // grootste sample en kleinste van elkaar aftrekken om de peak-peak amplitude te bekomen
   uint32_t volts = ((Mean * 3.3) / 1024)*100;  // convert naar  voltage
   Serial.println(volts);                             //voltage in serial monitor weergeven
 
      // zend een 'M' type bericht naar de raspberry pi
    if (!mesh.write(&volts, 'M', sizeof(volts))) 
  {
      // If a write fails, check connectivity to the mesh network
      if (! mesh.checkConnection()) 
    {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } 
    else 
    {
        Serial.println("Send fail, Test OK");
      }
    } 
  else 
  {
      Serial.println("Send OK: ");
    }
  }
}






