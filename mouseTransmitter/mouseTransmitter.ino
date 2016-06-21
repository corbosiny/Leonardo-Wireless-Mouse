#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

int xPin = A0;
int yPin = A1;
int clickPin = A2;

int switchPinA = 4;
int switchPinB = 5;

bool pausing = false;

int addresses = 0xF0F0F0F0E1LL;

int joyStickReadings[3];

RF24 radio(9, 10);

void setup() 
{

  Serial.begin(9600);

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(10, 15);
  radio.openWritingPipe(addresses);

  pinMode(switchPinA, OUTPUT);
  pinMode(switchPinB, OUTPUT);

  digitalWrite(switchPinA, HIGH);
  digitalWrite(switchPinB, LOW);
  
}

void loop() 
{

   //while(digitalRead(switchPinB) == LOW)
   //{

     // pausing = true;

      joyStickReadings[0] = (readXValues() + readXValues() + readXValues()) / 3;
      joyStickReadings[1] = (readYValues() + readYValues() + readYValues()) / 3;
      joyStickReadings[2] = (readClickValues() + readClickValues() + readClickValues()) / 3;

      while(!radio.write(&joyStickReadings, sizeof(joyStickReadings)));

   //}

   if(pausing == true)
   {

      pausing = false;

      joyStickReadings[0] = 512;
      joyStickReadings[1] = 512;
      joyStickReadings[2] = 512;

      radio.write(&joyStickReadings, sizeof(joyStickReadings));

   }

   Serial.println("Paused");
   delay(500);
   
}

int readXValues()
{

  int reading = analogRead(xPin);
  delay(20);
  return reading;
  
}

int readYValues()
{

  int reading = analogRead(yPin);
  delay(20);
  return reading;

}

int readClickValues()
{

  int reading = analogRead(clickPin);
  delay(20);
  return reading;

}
