
int buttonPin1 = 5;
int ledPin1 = 2;
int buttonPin2 = 6;
int ledPin2 = 3;

void setup() {

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

}

void loop() {

  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);


  if (buttonState1 == HIGH)
  {
    digitalWrite(ledPin1, HIGH);
  }
  else
  {
    digitalWrite(ledPin1, LOW);
  }

  if (buttonState2 == HIGH)
  {
    digitalWrite(ledPin2, HIGH);
  }
  else
  {
    digitalWrite(ledPin2, LOW);
  }

}
