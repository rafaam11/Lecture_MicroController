int led = 5;
int bright = 0;
int fade = 15;

void setup() {

pinMode(led,OUTPUT);

}

void loop() {

bright = bright + fade;
if (bright <= 0 || bright >= 255)
{
  fade = -fade;
}
analogWrite(led,bright); delay(100);

}
