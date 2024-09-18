#include <stdio.h>
#define MACRO "안녕하십니까 교수님ㅎㅎ"

void setup(){
  int num;
  num = 13579;
  Serial.begin(9600);
  Serial.println("문자열 프린트문");
  Serial.print("My name is "); Serial.println(num);
  Serial.print("print MACRO:"); Serial.print(MACRO);
}

void loop() {
  
}
