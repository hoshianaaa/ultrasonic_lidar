// SG-5010
//  制御パルス:0.5~2.4ms
//  pwmサイクル:20ms

#include <FlexiTimer2.h>

const int servo = 3;
volatile int servo_pulse_ = 0;//最適化を防ぐためvolatileをつける

void flash() {
  digitalWrite(servo, HIGH);
  delayMicroseconds(servo_pulse_);
  digitalWrite(servo, LOW);
}

void servo_write(int ang){
  //180 ~ 0 deg ==== 600 ~ 2400 ms
  int pulse = map(ang,180,0,600,2400);
  servo_pulse_ = pulse;
}

void setup() {
  Serial.begin(9600);

  pinMode(servo, OUTPUT);
  FlexiTimer2::set(20, flash); // 500ms period
  FlexiTimer2::start();
}

void loop() {
  
}
