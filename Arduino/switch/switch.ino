int button=14;                  // 変数buttonに14を代入する
int led=13;                     // 変数ledに13を代入する
void setup(){
  pinMode(button, INPUT);// buttonピンをプルアップ入力にする
  pinMode(led, OUTPUT);         // ledピンを出力にする
  digitalWrite(led, LOW); 
}
void loop(){
  if(digitalRead(button)==LOW){ // buttonピンがLOWならば
    Serial.println("2");
    digitalWrite(led, HIGH);    // ledピンにHIGHを出力する
    delay(3000);                // 3秒待つ
    digitalWrite(led, LOW);     // ledピンにLOWを出力する
  }
}
