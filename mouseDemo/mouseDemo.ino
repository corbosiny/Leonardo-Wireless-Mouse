int xPin = A0;
int yPin = A1;
int clickPin = A2;

int switchPin = 5;
bool justStarting = true;

void setup() {

  Serial.begin(9600);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(switchPin) == HIGH && justStarting)
  {

    Keyboard.begin();
    Mouse.begin();
    justStarting = false;
    
  }

  while(justStarting == false)
  {

    if(analogRead(clickPin) < 290 && !Mouse.isPressed()) {Mouse.press();}
    else if(analogRead(clickPin) > 320 && Mouse.isPressed()) {Mouse.release();}

    if(analogRead(xPin) > 600) {Mouse.move(10, 0, 0);}
    else if(analogRead(xPin) < 400) {Mouse.move(-10, 0, 0);}
    if(analogRead(yPin) > 600) {Mouse.move(0, 10 ,0);}
    else if(analogRead(yPin) < 400) {Mouse.move(0, -10 ,0);}

    if(digitalRead(switchPin == LOW)) {justStarting = true;}

    delay(75);

  }
  
}
