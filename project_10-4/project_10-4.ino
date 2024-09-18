int LEDpins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int NumLEDs = 8;
int digitmap[8][8] =
{
  {0, 0, 0, 1, 0, 0, 0, 1}, //A
  {1, 1, 0, 0, 0, 0, 0, 1}, //b
  {0, 1, 1, 0, 0, 0, 1, 1}, //C
  {1, 0, 0, 0, 0, 1, 0, 1}, //d
  {0, 1, 1, 0, 0, 0, 0, 1}, //E
  {0, 1, 1, 1, 0, 0, 0, 1}, //F
  {0, 1, 0, 0, 0, 0, 1, 1}, //G
  {1, 0, 0, 1, 0, 0, 0, 1}, //H
};

void setup()
{
  int i;
  for (int i = 0 ; i < NumLEDs; i++)
  {
    pinMode(LEDpins[i], OUTPUT);
  }

}

void loop()
{
  int i, j;
  for (i = 0 ; i < 8 ; i++)
  {
    for (j = 0 ; j < NumLEDs ; j++)
    {
      digitalWrite(LEDpins[j], digitmap[i][j]);
    }
    delay(500);
  }

}
