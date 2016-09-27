/*
  Example for receiving
  
  http://code.google.com/p/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("begin");
  pinMode(3, INPUT);  
  mySwitch.enableReceive(1);  // Receiver on inerrupt 0 => that is pin #2
  Serial.println("ready");  
}

void loop() {
  if (mySwitch.available()) {
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
}
