int xPin = A0;
int yPin = A1;
int clickPin = A2;

int joyStickReadings[3];

void setup() 
{

   Serial.begin(9600);

}

void loop() 
{

      joyStickReadings[0] = (readXValues() + readXValues() + readXValues()) / 3;
      joyStickReadings[1] = (readYValues() + readYValues() + readYValues()) / 3;
      joyStickReadings[2] = (readClickValues() + readClickValues() + readClickValues()) / 3;
    
      for(int x = 0; x < 3; x++)
      {

        Serial.println(joyStickReadings[0]);

      }

      delay(320);

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
