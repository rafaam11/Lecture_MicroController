#define TRIGPin 12
#define ECHOPin 13
int distance()
{
  int duration, cm;
  digitalWrite(TRIGPin, LOW); //making a pulse
  delayMicroseconds(2); //
  digitalWrite(TRIGPin, HIGH); //
  delayMicroseconds(10); //
  digitalWrite(TRIGPin, LOW); //
  duration = pulseIn(ECHOPin, HIGH); //receiving the echo
  // convert the time into a distance
  cm = duration / 29 / 2;
  return (cm);
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIGPin, OUTPUT);
  pinMode(ECHOPin, INPUT);
}

void loop() {

  int length;
  length = distance();
  delay(100);
  Serial.print("Distance = ");
  Serial.println(length);
}
