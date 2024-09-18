/* 미니 프로젝트1: 기계시스템공학과 20150339 김진민 */

int led[4] = {3, 5, 6, 9};       // PWM제어를 위해 led핀을 각각 3,5,6,9번 디지털 핀으로 설정

int button1 = 12;   // 버튼 2개의 핀을 각각 12,13번 디지털 핀으로 설정
int button2 = 13;

int pot = A1;       // 가변저항의 핀을 A1번 아날로그 핀으로 설정

int Bright = 0;
int fade = 50;
int potValue;
boolean bState1;
boolean bState2;

void setup() {

  Serial.begin(9600);

  for (int i = 0; i < 4; i++)
  {
    pinMode(led[i], OUTPUT);
  }

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT);

}


void loop() {

  int bState1 = digitalRead(button1);
  int bState2 = digitalRead(button2);
  delay(10);

  int potValue = analogRead(pot);
  potValue = map(potValue, 0, 1023, 0, 1000);
  Serial.print("가변저항상태:"); Serial.print(potValue);
  Serial.print(" 버튼1상태:"); Serial.print(bState1);
  Serial.print(" 버튼2상태:"); Serial.print(bState2);
  Serial.print(" 밝기상태:"); Serial.println(Bright);
  delay(100);

  if ( potValue <= 200)
  {
    for ( int q = 0 ; q < 4 ; q++)
    {
      analogWrite(led[q], 0);
    }
  }

  else if ( potValue <= 400)
  {
    if ( bState1 == LOW)
    {
      Bright = Bright + fade;
      if ( Bright >= 255)
      {
        Bright = 255;
      }
      
    }
    else if ( bState2 == LOW)
    {
      Bright = Bright - fade;
      if ( Bright <= 0)
      {
        Bright = 0;
      }
      
    }

    analogWrite(led[0], Bright);
    analogWrite(led[1], 0);
    analogWrite(led[2], 0);
    analogWrite(led[3], 0);

  }
  else if ( potValue <= 600)
  {
    if ( bState1 == LOW)
    {
      Bright = Bright + fade;
      if ( Bright >= 255)
      {
        Bright = 255;
      }
      
    }
    else if ( bState2 == LOW)
    {
      Bright = Bright - fade;
      if ( Bright <= 0)
      {
        Bright = 0;
      }
     
    }

    analogWrite(led[0], Bright);
    analogWrite(led[1], Bright);
    analogWrite(led[2], 0);
    analogWrite(led[3], 0);

  }
  else if ( potValue <= 800)
  {
    if ( bState1 == LOW)
    {
      Bright = Bright + fade;
      if ( Bright >= 255)
      {
        Bright = 255;
      }
     
    }
    else if ( bState2 == LOW)
    {
      Bright = Bright - fade;
      if ( Bright <= 0)
      {
        Bright = 0;
      }
     
    }

    analogWrite(led[0], Bright);
    analogWrite(led[1], Bright);
    analogWrite(led[2], Bright);
    analogWrite(led[3], 0);

  }
  else if ( potValue <= 1000)
  {
    if ( bState1 == LOW)
    {
      Bright = Bright + fade;
      if ( Bright >= 255)
      {
        Bright = 255;
      }
     
    }
    else if ( bState2 == LOW)
    {
      Bright = Bright - fade;
      if ( Bright <= 0)
      {
        Bright = 0;
      }
     
    }

    analogWrite(led[0], Bright);
    analogWrite(led[1], Bright);
    analogWrite(led[2], Bright);
    analogWrite(led[3], Bright);

  }


}
