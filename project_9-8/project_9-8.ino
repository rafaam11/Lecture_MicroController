#define TRIGPin 12
#define ECHOPin 13
int ledPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGPin, OUTPUT);
  pinMode(ECHOPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  long duration, cm;
  digitalWrite(TRIGPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPin, LOW);
  duration = pulseIn(ECHOPin, HIGH);
  cm = duration / 29 / 2;
  Serial.print(cm);
  Serial.println(" cm");

  int bright = 10 * cm;
  if ( cm >= 25 )
  {
    bright = 255;
  }
  if ( cm < 2 )
  {
    bright = 0;
  }
  analogWrite(ledPin, bright);
  delay(100);
}
