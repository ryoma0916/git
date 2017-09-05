#include "Keyboard.h"

#define Button1 15

void setup() {
  Keyboard.begin();
  pinMode(Button1, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(Button1) == LOW){
    Keyboard.print("j8o8j ");
    Keyboard.write('\n');
    delay(100);

    while(digitalRead(Button1) == LOW);
  }

  delay(100);
}
