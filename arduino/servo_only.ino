#include <Servo.h>
const int serv_pin = 12;

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(serv_pin);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.write(180);

}
