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

void setup() {
  Serial.begin(9600);

  pinMode(servo, OUTPUT);
  FlexiTimer2::set(20, flash); // 500ms period
  FlexiTimer2::start();
}

void loop() {
  servo_pulse_ = 600;//180 deg
  delay(1000);
  servo_pulse_ = 2400;//0 deg
  delay(1000);
}
