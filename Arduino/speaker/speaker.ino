#define BEAT 300   // 音の長さを指定
#define PINNO 12   // 圧電スピーカを接続したピン番号

void setup() {
}
void loop() {
     tone(PINNO,262,BEAT) ;  // ド
     delay(BEAT) ;
     tone(PINNO,294,BEAT) ;  // レ
     delay(BEAT) ;
     tone(PINNO,330,BEAT) ;  // ミ
     delay(BEAT) ;
     tone(PINNO,349,BEAT) ;  // ファ
     delay(BEAT) ;
     tone(PINNO,392,BEAT) ;  // ソ
     delay(BEAT) ;
     tone(PINNO,440,BEAT) ;  // ラ
     delay(BEAT) ;
     tone(PINNO,494,BEAT) ;  // シ
     delay(BEAT) ;
     tone(PINNO,523,BEAT) ;  // ド
     delay(3000) ;           // ３秒後に繰り返す
}
