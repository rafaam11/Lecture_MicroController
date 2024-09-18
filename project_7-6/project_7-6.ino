int led = 5;
int bright;
int fade = 15;


int Ledon(int dtime)
{
  int y = 1.5 * dtime;
  analogWrite(led, bright);
  delay(y);
  return (y);
}

void setup()
{

  pinMode(led, OUTPUT);
  Serial.begin(9600);

}
void loop()
{

  int x;
  for (bright = 0; bright <= 255; bright = bright + fade)
  {
    x = Ledon(100);
    Serial.println(x);
  }
}
