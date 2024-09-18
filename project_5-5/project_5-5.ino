
int ledPins[5] = { 4, 6, 8, 10, 12 };
int index;

void setup() {

  for (index = 0; index <= 4; index++)
  {
    pinMode(ledPins[index], OUTPUT);
  }

}
void loop() {

  for (index = 0; index <= 4 ; index++)
  {
    digitalWrite(ledPins[index],HIGH);
    delay(100);
  }

  for (index = 4; index >= 0 ; index--)
  {
    digitalWrite(ledPins[index],LOW);
    delay(100);
  }
  
}
