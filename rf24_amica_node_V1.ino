/*  Written by Steve Lovejoy aka lovejoy777.
 *   
 *  Heating Node code for the arduino nano with
 *  rf24Lo1 rf module.
 *  
 *  connect 5v from power supply to vin nano and 0v to gnd nano.
 *  
 * rf24 pin config for nano
 ******************************
 *  VCC = 3v3 nano            *
 *  GND = gnd nano            *
 *  CE = pin9 nano;           *
 *  CSN = pin10 nano;         *
 *  MOSI = pin 11 nano;       *
 *  MISO = pin 12 nano;       *    
 *  SCK = pin 13 nano;        *
 ******************************
 *  
 *  solder 10uf accross vcc & gnd at rf24L01
 *  
 *  I also have a relay to pin D2 & gnd nano.
 *  
 *  still need to move temperature sensor from base station to node
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte rxAddr[6] = "00001";
const byte txAddr[6] = "00002";

#define relay1 2

void setup()
{
  pinMode(relay1, OUTPUT);
  
  while (!Serial);
  Serial.begin(57600);
  
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.openWritingPipe(txAddr);
  
  //radio.startListening();
  Serial.print("Setup Done");
}

void loop()
{
  radio.startListening();
  delay(100);
  
  if (radio.available())
  {
    int i = 0;
    radio.read(&i, sizeof(i));

    Serial.print("received ");
    Serial.println(i);

    delay(100);

    if (i == 9997) {
      digitalWrite(relay1,HIGH); // on
      radio.stopListening();
      delay(100);
      int akrelay1On = 9957;
      Serial.print("sending ");
      Serial.println(akrelay1On);
      radio.write(&akrelay1On, sizeof(akrelay1On));
      delay(100);
      
    }

    if (i == 9998) {
      digitalWrite(relay1,LOW); // on
      radio.stopListening();
      delay(100);
      int akrelay1Off = 9958;
      Serial.print("sending ");
      Serial.println(akrelay1Off);
      radio.write(&akrelay1Off, sizeof(akrelay1Off));
      delay(100);
    }
    
  }
  
  delay(500);
}
