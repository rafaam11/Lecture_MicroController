
int ledPins[5] = { 4, 6, 8, 10, 12 };
int index;

void setup() {

  for (index = 0; index <= 4; index++)
  {
    pinMode(ledPins[index], OUTPUT);
  }

}
void loop() {

  int Random1 = rand() % 5;
  if ( Random1 == 0 )
  {
    digitalWrite(ledPins[0], HIGH);
    delay(1000);
    digitalWrite(ledPins[0], LOW);
  }
  if ( Random1 == 1 )
  {
    digitalWrite(ledPins[1], HIGH);
    delay(1000);
    digitalWrite(ledPins[1], LOW);
  }
  if ( Random1 == 2 )
  {
    digitalWrite(ledPins[2], HIGH);
    delay(1000);
    digitalWrite(ledPins[2], LOW);
  }
  if ( Random1 == 3 )
  {
    digitalWrite(ledPins[3], HIGH);
    delay(1000);
    digitalWrite(ledPins[3], LOW);
  }
  if ( Random1 == 4 )
  {
    digitalWrite(ledPins[4], HIGH);
    delay(1000);
    digitalWrite(ledPins[4], LOW);
  }


  
}
