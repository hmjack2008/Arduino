#include <RemoteReceiver.h>

/*
* Demo for RF remote switch receiver.
* For details, see RemoteReceiver.h!
*
* This sketch shows the received signals on the serial port.
* Connect the receiver to digital pin 2.
*/

int LED = 13;
RemoteReceiver RemoteReceiver_A;
// RemoteReceiver RemoteReceiver_B;

void setup() {
  Serial.begin(115200);
  delay(8000);
  Serial.println("ready");
  
  //Initialize receiver on interrupt 0 (= digital pin 2), calls the callback "showCode"
  //after 3 identical codes have been received in a row. (thus, keep the button pressed
  //for a moment)
  //
  //See the interrupt-parameter of attachInterrupt for possible values (and pins)
  //to connect the receiver.
  RemoteReceiver_A.init(0, 3, showCode_A);
//  RemoteReceiver_B.init(1, 3, showCode_B);
  
  pinMode(LED, OUTPUT);
}

int LEDstatus = HIGH;
void loop() {
  digitalWrite(LED, LEDstatus);
  LEDstatus = !LEDstatus;
  delay(2000);
}

//Callback function is called only when a valid code is received.
void showCode_A(unsigned long receivedCode, unsigned int period) {
  //Note: interrupts are disabled. You can re-enable them if needed.
  
  //Print the received code.
  Serial.print("A-code: ");
  Serial.print(receivedCode, BIN);
  Serial.print("  ");
  Serial.print(receivedCode);
  Serial.print(", period duration: ");
  Serial.print(period);
  Serial.println("us.");
  
  digitalWrite(LED, LEDstatus);
  LEDstatus = !LEDstatus;
}

//Callback function is called only when a valid code is received.
void showCode_B(unsigned long receivedCode, unsigned int period) {
  //Note: interrupts are disabled. You can re-enable them if needed.
  
  //Print the received code.
  Serial.print("B-code: ");
  Serial.print(receivedCode, BIN);
  Serial.print("  ");
  Serial.print(receivedCode);
  Serial.print(", period duration: ");
  Serial.print(period);
  Serial.println("us.");
  
  digitalWrite(LED, LEDstatus);
  LEDstatus = !LEDstatus;
}
