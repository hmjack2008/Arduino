/*
  Example for different sending methods
  
  http://code.google.com/p/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int LED = 13;
int statusLED = HIGH;

void setup() {

  Serial.begin(115200);
  Serial.println("ready");
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(350);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(8); 
  
  pinMode(LED, OUTPUT);
  
}

void loop() {
  
  digitalWrite(LED, HIGH);

  /* Same switch as above, but using binary code */
  /*
A-code: 10000001101001110111  531063, period duration: 460us.
A-code: 10000001101001011111  531039, period duration: 462us.
A-code: 10000001101001111010  531066, period duration: 461us.
A-code: 10000001101010011000  531096, period duration: 489us.
A-code: 10000001101111110000  531440, period duration: 496us.
A-code: 10000001101111101101  531437, period duration: 495us.  
  */
  
  mySwitch.setPulseLength(460);
  mySwitch.send("000010000001101001110111"); //24 bits
  delay(1000);  //5
  mySwitch.send("000010000001101001011111"); //24 bits
  delay(1000);  //5
  mySwitch.send("000010000001101001011111"); //24 bits
  delay(1000);  //5
  mySwitch.setPulseLength(490);
  mySwitch.send("000010000001101010011000"); //24 bits
  delay(1000);  //5
  mySwitch.send("000010000001101111110000"); //24 bits
  delay(1000);  //5
  mySwitch.send("000010000001101111101101"); //24 bits
  delay(1000);  //5  

  digitalWrite(LED, LOW);

  Serial.println("send.");
  delay(4000);
}
