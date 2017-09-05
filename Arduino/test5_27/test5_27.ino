#include "Keyboard.h"

#define Button1 15
#define Button2 14
#define Button3 10
#define Button4 9

void setup() {
  Keyboard.begin();
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(Button1) == LOW) { // コピー
    Keyboard.print("a"); Keyboard.write('\n');
   
    while (digitalRead(Button1) == LOW);
  }
  
    if (digitalRead(Button2) == LOW) { // コピー
    Keyboard.print("b"); Keyboard.write('\n');
   
    while (digitalRead(Button2) == LOW);
  }
  
    if (digitalRead(Button3) == LOW) { // コピー
    Keyboard.print("c"); Keyboard.write('\n');
   
    while (digitalRead(Button3) == LOW);
  }
  
    if (digitalRead(Button4) == LOW) { // コピー
    Keyboard.print("d"); Keyboard.write('\n');
   
    while (digitalRead(Button4) == LOW);
  }

  delay(100);
}
