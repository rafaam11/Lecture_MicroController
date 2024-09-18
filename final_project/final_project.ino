#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247

#define C4 261
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494

#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 988

#define C6 1046
#define D6 1175
#define E6 1318
#define F6 1397
#define G6 1568
#define A6 1760
#define B6 1975
#define C7 2093

int ledpin[] = {2, 3, 4};
int buzzer = 5;
int button[] = {6, 7, 8, 9, 10, 11, 12, 13};
int pot = A0;
int tone_height;
int tone_f[][8] = {{C3, D3, E3, F3, G3, A3, B3, C4}, {C4, D4, E4, F4, G4, A4, B4, C5}, {C5, D5, E5, F5, G5, A5, B5, C6}, {C6, D6, E6, F6, G6, A6, B6, C7}};
boolean b1;
boolean b2;
boolean b3;
boolean b4;
boolean b5;
boolean b6;
boolean b7;
boolean b8;
String text;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(ledpin[0], OUTPUT);
  pinMode(ledpin[1], OUTPUT);
  pinMode(ledpin[2], OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button[0], INPUT_PULLUP);
  pinMode(button[1], INPUT_PULLUP);
  pinMode(button[2], INPUT_PULLUP);
  pinMode(button[3], INPUT_PULLUP);
  pinMode(button[4], INPUT_PULLUP);
  pinMode(button[5], INPUT_PULLUP);
  pinMode(button[6], INPUT_PULLUP);
  pinMode(button[7], INPUT_PULLUP);
  Serial.begin(9600);

}

void playTone(int tone_height)
{
  if ( b1 == LOW)
  {
    tone(buzzer, tone_f[tone_height][0]);
    text = "//              ";
    tone_lcd_print(text);
    
  }
  else if ( b2 == LOW)
  {
    tone(buzzer, tone_f[tone_height][1]);
    text = "////            ";
    tone_lcd_print(text);
  }
  else if ( b3 == LOW)
  {
    tone(buzzer, tone_f[tone_height][2]);
    text = "//////          ";
    tone_lcd_print(text);
  }
  else if ( b4 == LOW)
  {
    tone(buzzer, tone_f[tone_height][3]);
    text = "////////        ";
    tone_lcd_print(text);
  }
  else if ( b5 == LOW)
  {
    tone(buzzer, tone_f[tone_height][4]);
    text = "//////////      ";
    tone_lcd_print(text);
  }
  else if ( b6 == LOW)
  {
    tone(buzzer, tone_f[tone_height][5]);
    text = "////////////    ";
    tone_lcd_print(text);
  }
  else if ( b7 == LOW)
  {
    tone(buzzer, tone_f[tone_height][6]);
    text = "//////////////  ";
    tone_lcd_print(text);
  }
  else if ( b8 == LOW)
  {
    tone(buzzer, tone_f[tone_height][7]);
    text = "////////////////";
    tone_lcd_print(text);
  }
  else
  {
    noTone(buzzer);
  }

}

void tone_lcd_print(String text) {

  lcd.setCursor(0, 1);
  lcd.print(text);

}


void loop() {

  b1 = digitalRead(button[0]);
  b2 = digitalRead(button[1]);
  b3 = digitalRead(button[2]);
  b4 = digitalRead(button[3]);
  b5 = digitalRead(button[4]);
  b6 = digitalRead(button[5]);
  b7 = digitalRead(button[6]);
  b8 = digitalRead(button[7]);
  int potValue = analogRead(pot);
  potValue = map(potValue, 0, 1023, 0, 1000);

  if ( potValue < 250 )
  {
    tone_height = 0;
    lcd.setCursor(0, 0);
    lcd.print("Octave : 2      ");
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    playTone(tone_height);


  }
  else if ( potValue < 500 )
  {
    tone_height = 1;
    lcd.setCursor(0, 0);
    lcd.print("Octave : 3      ");
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    playTone(tone_height);
  }
  else if ( potValue < 750 )
  {
    tone_height = 2;
    lcd.setCursor(0, 0);
    lcd.print("Octave : 4      ");
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], LOW);
    playTone(tone_height);
  }
  else
  {
    tone_height = 3;
    lcd.setCursor(0, 0);
    lcd.print("Octave : 5      ");
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], HIGH);
    playTone(tone_height);
  }











}
