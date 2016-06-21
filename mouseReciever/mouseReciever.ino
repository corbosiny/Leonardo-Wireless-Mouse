#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

int switchPinA = 4;
int switchPinB = 5;

bool justStarting = true;

int addresses = 0xF0F0F0F0E1LL;

int joyStickReadings[3];

RF24 radio(9,10);

void setup() {

  Serial.begin(9600);

  pinMode(switchPinA, OUTPUT);
  pinMode(switchPinB, OUTPUT);

  digitalWrite(switchPinA, HIGH);
  digitalWrite(switchPinB, LOW);

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(10, 15);
  radio.openReadingPipe(1, addresses);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(switchPinB) == LOW && justStarting)
  {

    Keyboard.begin();
    Mouse.begin();
    justStarting = false;
    
  }

  while(digitalRead(switchPinB == LOW) && !justStarting)
  {

    if(radio.available())
    {

      radio.read(&joyStickReadings, sizeof(joyStickReadings));
    
      if(analogRead(joyStickReadings[2]) < 290 && !Mouse.isPressed()) {Mouse.press();}
      else if(analogRead(joyStickReadings[2]) > 320 && Mouse.isPressed()) {Mouse.release();}

      if(analogRead(joyStickReadings[0]) > 600) {Mouse.move(10, 0, 0);}
      else if(analogRead(joyStickReadings[0]) < 400) {Mouse.move(-10, 0, 0);}
      if(analogRead(joyStickReadings[1]) > 600) {Mouse.move(0, 10 ,0);}
      else if(analogRead(joyStickReadings[1]) < 400) {Mouse.move(0, -10 ,0);}

    }

    delay(25);

  }

  justStarting = true;
  
}
