#define TRIGPin 12
#define ECHOPin 13
int buzPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGPin, OUTPUT);
  pinMode(ECHOPin, INPUT);
  pinMode(buzPin, OUTPUT);
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
  delay(100);

  if ( cm <= 10 )
  {
    tone(buzPin, 300);
  }
  else
  {
    noTone(buzPin);
  }

}
