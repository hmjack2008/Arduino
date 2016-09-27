/*
 * Serial Tx/Rx
#ifdef SERIAL_USB // add-in board.h
  Serial,  USB, PA11 PA12
  Serial1, PA9, PA10 USART1
  Serial2, PA2, PA3  USART2
  Serial3, PB10,PB11 USART3
  ----------------------------------------------
#ifndef SERIAL_USB
  Serial,  PA9, PA10 USART1
  Serial1, PA2, PA3  USART2
  Serial2, PB10,PB11 USART3
*/

// USBSerial SerialUSB;

void setup() {
  delay(5000);
  
  Serial.begin(9600);
  delay(100);
  Serial.println("Serial 0 begin ...");
  
  Serial1.begin(9600);
  delay(100);
  Serial1.println("Serial 1 begin ...");

  Serial2.begin(9600);
  delay(100);
  Serial2.println("Serial 2 begin ...");
#ifdef SERIAL_USB
  // SerialUSB.begin(9600);
  Serial3.begin(9600);
  delay(100);
  Serial3.println("Serial 3 begin ...");
  Serial1.println("Serial 1->3 begin ...");
#endif  
}
void loop() {
   Serial.println("Serial 0");
  Serial1.println("Serial 1");
  Serial2.println("Serial 2");
#ifdef SERIAL_USB
  // SerialUSB.println("SerialUSB");
  Serial3.println("Serial 3");
  Serial1.println("Serial 1->3");
#endif
  delay(3000);
}
