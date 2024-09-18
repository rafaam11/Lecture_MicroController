
int buttonPin = 5;
int ledPin = 3;

void setup() {

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {

  int buttonState;
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }

  else
  {
    digitalWrite(ledPin, LOW);
  }

}
