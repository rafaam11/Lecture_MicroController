int in1 = 9;
int in2 = 8;
int ena = 10;
int in3 = 3;
int in4 = 4;
int enb = 5;

void setup() {
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(ena,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(enb,OUTPUT);
}

void loop() {

digitalWrite(in1,HIGH); digitalWrite(in3,HIGH);
digitalWrite(in2,LOW); digitalWrite(in4,LOW);
analogWrite(ena,100); analogWrite(enb,100);
delay(2000);

digitalWrite(in1,LOW); digitalWrite(in3,LOW);
digitalWrite(in2,HIGH); digitalWrite(in4,HIGH);
analogWrite(ena,200); analogWrite(enb,200);
delay(2000);

}
