const int ledPin[3] = { 3, 5, 6 };
const int sensorPin = A1;

int sensorout;

void setup() {

  for ( int i = 0 ; i <= 2 ; i++)
  {
    pinMode(ledPin[i], OUTPUT);
  }

}

void loop() {
  sensorout = analogRead(sensorPin);

  if ( sensorout <= 250 ) {
    for ( int i = 0 ; i <= 2 ; i ++ )
    {
      digitalWrite(ledPin[i], LOW);
    }

  }
  else if ( sensorout <= 500 ) {

    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], LOW);
    
  }
  else if ( sensorout <= 750 ) {
    
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], LOW);

  }
  else if ( sensorout <= 1023 ) {
    
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);

  }
  delay(500);

}
