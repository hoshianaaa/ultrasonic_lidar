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
  // SG-5010
  //制御パルス:0.5~2.4ms
  //pwmサイクル:20ms
  
  // ServoLibrary:1~2ms->使えない
  
  
  myServo.write(180);
  

}
