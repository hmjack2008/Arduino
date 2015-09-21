/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int LED = 13;

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("begin");
  pinMode(3, INPUT);
  mySwitch.enableReceive(1);  // Receiver on inerrupt 0 => that is pin #2
  Serial.println("ready");
  
  pinMode(LED, OUTPUT);
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      digitalWrite(LED, HIGH);
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue(), BIN );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      digitalWrite(LED, LOW);
    }

    mySwitch.resetAvailable();
  }
}
