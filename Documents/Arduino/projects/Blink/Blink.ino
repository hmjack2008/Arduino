/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = 13;
int led_size = 32; // D1 .. D13 .. D31

// the setup routine runs once when you press reset:
void setup() {         

  Serial.begin(9600);
  delay(5000);
  Serial.println("Serial ready");

  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  for (int i=2; i<led_size; i++)  pinMode(i, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial.println("--- serial 0 ---");
  
//  
//  // read analog inputs and set X-Y position
//  Joystick.X(48);
//  Joystick.Y(32);
//  delay(1000);
//  
//  Joystick.X(511);
//  Joystick.Y(511);
//  
//
//  // read the digital inputs and set the buttons
//  Joystick.button(1, 1);
//  delay(200);
//  Joystick.button(1, 0);
//  
//  for (int i=0; i<10; i++)  Mouse.move(2, 2);
//  
//  
  
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  for (int i=2; i<led_size; i++)  digitalWrite(i, HIGH);
  delay(200);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  for (int i=2; i<led_size; i++)  digitalWrite(i, LOW);
  delay(1000);               // wait for a second
}
