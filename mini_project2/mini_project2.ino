#define BUZZER 11 // 부저를 11번 핀
#define TRIGPin 12 // 초음파센서 트리거 12
#define ECHOPin 13 //초음파 센서 에코 13
int count = 0; // 물체 감지 회수
int LEDpins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int NumLEDs = 8; // LED 개수
// 도, 레, 미, 파, 솔, 라, 시, 도
int tone_f[] = {261, 294, 330, 349, 392, 440, 494, 523};
int digitmap[10][8] = { //숫자에 대한 맵 (0 ~ 9)
  {0, 0, 0, 0, 0, 0, 1, 1}, //0
  {1, 0, 0, 1, 1, 1, 1, 1}, //1
  {0, 0, 1, 0, 0, 1, 0, 1}, //2
  {0, 0, 0, 0, 1, 1, 0, 1}, //3
  {1, 0, 0, 1, 1, 0, 0, 1}, //4
  {0, 1, 0, 0, 1, 0, 0, 1}, //5
  {0, 1, 0, 0, 0, 0, 0, 1}, //6
  {0, 0, 0, 1, 1, 1, 1, 1}, //7
  {0, 0, 0, 0, 0, 0, 0, 1}, //8
  {0, 0, 0, 0, 1, 0, 0, 1} //9
};

// 7 세그먼트 함수
void sevSEG(int i) {
  for (int j = 0 ; j < NumLEDs ; j++) { //Turn on or off the LEDs
    digitalWrite(LEDpins[j], digitmap[i][j]);
  }
  delay(10);
}

// 부저함수
void play() {
  for (int i = 0; i < 2; i++)
  {
    tone(BUZZER, tone_f[0]); //play DO-Do
    delay(500);
    tone(BUZZER, tone_f[7]);
    delay(500);
  }
  noTone(BUZZER); // 소리 중단
}

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

  pinMode(BUZZER, OUTPUT);
  pinMode(TRIGPin, OUTPUT);
  pinMode(ECHOPin, INPUT);
  for (int pin = 0 ; pin < 8 ; pin++)
  {
    pinMode(LEDpins[pin], OUTPUT);
  }
  sevSEG(0);

}

void loop () {

  distance();
  delay(100);
  while ( distance() < 30 )
  {
    count++;
    delay(500);
    sevSEG(count);
    if ( count > 9 )
    {
      play();
      count = 0;
      sevSEG(0);
      break;
    }

  }



}
