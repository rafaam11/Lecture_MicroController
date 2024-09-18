#define MACRO "this is a macro"
void setup() /* sketch 실행 시 1번만 실행, run only once*/
{
int num; 
num=1;
Serial.begin(9600);
Serial.println("I am a simple program."); 
Serial.print("My number is "); Serial.print(num); 
Serial.print(" print MACRO : "); Serial.print(MACRO);
}
void loop() /* 무한 반복 실행, run repeatedly */
{
} 
