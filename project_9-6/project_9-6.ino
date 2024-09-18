#include <dht.h>
dht DHT;
int DHTpin = A1;
float humidity, temperature;

void setup() {

  Serial.begin(9600);

}

void loop() {
  int value;
  value = DHT.read11(DHTpin);
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  Serial.print("check");
  Serial.print("T = "); Serial.print(temperature);
  Serial.print("H = "); Serial.println(humidity);
  delay(1000);
}
