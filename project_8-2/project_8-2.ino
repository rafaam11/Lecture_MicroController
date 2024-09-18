int sensorPin = A1;
int led = 5;

void setup() {
  
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
}
void loop() {
  
  int sensorValue;
  
  sensorValue = analogRead(sensorPin);
  Serial.print("potentiometer = ");
  Serial.println(sensorValue);
  
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(led, sensorValue);
  delay(100);
}
