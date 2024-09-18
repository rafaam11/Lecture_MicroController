int sensorPin = A0;
int led = 3;

void setup()
{
  
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
}
void loop()
{
  int sensorValue = 0;
  float voltage = 0.0;
  
  sensorValue = analogRead(sensorPin);
  voltage = ((float)sensorValue / 1023.0) * 5.0;
  Serial.println(sensorValue);
  Serial.println(voltage);
  
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(led, sensorValue);
  delay(100);
}
