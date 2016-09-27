/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Blink
  Basic example to test that HoodLoader2 works.

  You may also want to use:
  LED_BUILTIN
  LED_BUILTIN_RX
  LED_BUILTIN_TX
*/

const uint32_t blinkDelay = 3000;
const uint8_t pinLed = LED_BUILTIN;
const uint8_t pinLed_rx = LED_BUILTIN_RX;
const uint8_t pinLed_tx = LED_BUILTIN_TX;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize led as an output.
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed_rx, OUTPUT);
  pinMode(pinLed_tx, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pinLed, HIGH);
  digitalWrite(pinLed_rx, HIGH);
  digitalWrite(pinLed_tx, HIGH);    
  delay(blinkDelay);
  digitalWrite(pinLed, LOW);
  digitalWrite(pinLed_rx, LOW);  
  digitalWrite(pinLed_tx, LOW);  
  delay(blinkDelay);
}
