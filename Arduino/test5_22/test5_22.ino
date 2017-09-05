#include "Keyboard.h"

#define Button1 15
#define Button2 14
#define Button3 10

void setup() {
  Keyboard.begin();
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(Button1) == LOW) { // コピー
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('c');
    delay(50);
    Keyboard.releaseAll();

    while (digitalRead(Button1) == LOW);
  }
  if (digitalRead(Button2) == LOW) { //　ペースト
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('v');
    delay(50);
    Keyboard.releaseAll();

    while (digitalRead(Button2) == LOW);
  }
  if (digitalRead(Button3) == LOW) { //　ペースト
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('z');
    delay(50);
    Keyboard.releaseAll();

    while (digitalRead(Button3) == LOW);
  }
  delay(100);
}
