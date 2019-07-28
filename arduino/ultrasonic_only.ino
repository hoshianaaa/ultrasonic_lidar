int trig = 8; // 出力ピン
int echo = 9; // 入力ピン

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

int get_distance() {
  // 超音波の出力終了
  digitalWrite(trig, LOW);
  delayMicroseconds(1);
  // 超音波を出力
  digitalWrite(trig, HIGH);
  delayMicroseconds(11);
  // 超音波を出力終了
  digitalWrite(trig, LOW);
  // 出力した超音波が返って来る時間を計測
  long int t = pulseIn(echo, HIGH, 23500);  //4000~6000us  4m:23500us 
  
  // 計測した時間と音速から反射物までの距離を計算
  Serial.print("timt(us):");
  Serial.println(t);
  return  t * 0.17;
}

void loop() {

  Serial.println(get_distance());
  delay(500);
  
}
