// SG-5010
//  制御パルス:0.5~2.4ms
//  pwmサイクル:20ms

#include <FlexiTimer2.h>

//**** parameter *****//

const int delay_time_ = 0;//1deg間のdelay_time
const int data_count_ = 3;//1degに対するスキャンの回数
const float low_pass_ = 0.9;//高いほどノイズが減る(0~1.0)

////////////////////////

const int servo = 3;
const int trig = 8;
const int echo = 9;
volatile int servo_pulse_ = 0;//最適化を防ぐためvolatileをつける

void flash() {
  digitalWrite(servo, HIGH);
  delayMicroseconds(servo_pulse_);
  digitalWrite(servo, LOW);
}

void servo_write(int ang) {
  //180 ~ 0 deg ==== 600 ~ 2400 ms
  int pulse = map(ang, 180, 0, 600, 2400);
  servo_pulse_ = pulse;
}

int get_distance() {

  long int t = 0;
  for (int i = 0; i < data_count_; i++) {
    digitalWrite(trig, LOW);
    delayMicroseconds(1);
    digitalWrite(trig, HIGH);
    delayMicroseconds(11);
    digitalWrite(trig, LOW);
    t = t + pulseIn(echo, HIGH, 10000); //4000~6000us
  }
  return  t / data_count_ * 0.17;
}



void setup() {
  Serial.begin(9600);
  pinMode(servo, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  FlexiTimer2::set(20, flash); // 500ms period
  FlexiTimer2::start();
}

int low_pass_filter(int input) {
  static int data;
  if (input)data = data * low_pass_ + input * (1 - low_pass_);//inputが0の時無視する
  return data;
}

void loop() {

  static int last_data;
  int data;
  servo_write(0);
  delay(1000);
  if (Serial.read() == -1)return;
  Serial.print("\n+:");
  for (int i = 0; i <= 180; i += 2) {
    servo_write(i);
    //Serial.print(i);
    //Serial.print(" ");
    data = get_distance();
    Serial.print(low_pass_filter(data));
    Serial.print(",");
    delay(10);
  }

  Serial.print("0");


  if (Serial.read() == -1)return;
  Serial.print("\n-:");
  for (int i = 180; i > 0; i -= 2) {
    servo_write(i);
    //Serial.print(i);
    //Serial.print(" ");
    data = get_distance();
    Serial.print(low_pass_filter(data));
    Serial.print(",");
    delay(10);
  }
  Serial.print("0");

}
