# include <SevenSeg.h>
// string 표시
SevenSeg disp (6, 7, 8, 9, 10, 11, 12); //Dot 제외
int nDigits = 4;
int digitPins[ ] = {A2, A3, A4, A5}; //{16,17,18,19}
String str;

void setup () {
  disp.setDigitPins(nDigits, digitPins);
  disp.setCommonCathode();
  Serial.begin(9600);
}
void loop () {
  String str;
  char text[4];
  if (Serial.available()) {
    delay(10); // 시리얼 통신 완료를 위한 시간 지연.
    int i = 0;
    while (Serial.available()) {
      text[i] = (char) Serial.read(); // read the string in the buffer
      i++;
    }
  }
  str = text;
  disp.write (str) ;

}
