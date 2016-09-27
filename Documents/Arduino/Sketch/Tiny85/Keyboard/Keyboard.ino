#include "DigiKeyboard.h"

void setup() {
  // don't need to set anything up to use DigiKeyboard
  
  DigiKeyboard.delay(5000);
  
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(50);
  
  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
  DigiKeyboard.sendKeyPress(0,MOD_GUI_LEFT); // KEY_LEFT_GUI
  DigiKeyboard.delay(50);
/* 
  DigiKeyboard.sendKeyPress(0x15); // 'r'
  DigiKeyboard.delay(50);
  DigiKeyboard.sendKeyPress(0,0); // 'r'
  DigiKeyboard.delay(50); 
*/
  DigiKeyboard.sendKeyPress(0,0); // KEY_LEFT_GUI
  DigiKeyboard.delay(100);

  DigiKeyboard.println("notepad.exe");
  DigiKeyboard.delay(5000);
}


void loop() {

  DigiKeyboard.println("Hi, ATtiny85 .... !");

  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  DigiKeyboard.delay(5000);
}
