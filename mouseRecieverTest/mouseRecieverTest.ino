#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

int joyStickReadings[3];

int addresses = 0xF0F0F0F0E1LL;

RF24 radio(9, 10);

void setup() 
{

  Serial.begin(9600);

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(10, 15);
  radio.openReadingPipe(1, addresses);
  radio.startListening();
  
}

void loop() 
{

  if(radio.available())
  {

    Serial.println("Message Received");
    Serial.println("");

    radio.read(&joyStickReadings, sizeof(joyStickReadings));

    for(int x = 0; x < 3; x++) {Serial.println(joyStickReadings[x]);}

    Serial.println("");
    
  }

}
