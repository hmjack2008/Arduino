/*
* Connect the receiver to digital pin 2.
* Connect the transmitter to digital pin 11.
*/
#include <RemoteSwitch.h>

int tranPin_A = 10;
int tranPeriod_A = 350; // 350; // 128; //uSec
int tranRepeat_A = 4;
// Array of size 12 = 8-address and 4-data.
// "tranTrits[]" should be either 0, 1 or 2, where 2 indicaties "float"
unsigned short tranTrits_A[12] = {2,2,2,2,2,2,2,2,  0,1,0,1};
RemoteSwitch Transmitter_A(tranPin_A, tranPeriod_A, tranRepeat_A);

int tranPin_B = 11;
int tranPeriod_B = 128; // 350; // 128; //uSec
int tranRepeat_B = 4;
// Array of size 12 = 8-address and 4-data.
// "tranTrits[]" should be either 0, 1 or 2, where 2 indicaties "float"
unsigned short tranTrits_B[12] = {2,2,2,2,2,2,2,2,  0,1,0,1};
RemoteSwitch Transmitter_B(tranPin_B, tranPeriod_B, tranRepeat_B);
  
int LED = 13;

void setup() {
  Serial.begin(115200);
  delay(8000);
  Serial.println("ready");
  pinMode(LED, OUTPUT);
}

int LEDstatus = HIGH;
unsigned short i = 0;

void loop() {
  
      tranTrits_A[11] = (i & 0x01);
      tranTrits_A[10] = (i >> 1) & 0x01;
      tranTrits_A[9]  = (i >> 2) & 0x01;
      tranTrits_A[8]  = (i >> 3) & 0x01;
      tranTrits_B[8] = (i & 0x01);
      tranTrits_B[9] = (i >> 1) & 0x01;
      tranTrits_B[10]  = (i >> 2) & 0x01;
      tranTrits_B[11]  = (i >> 3) & 0x01;
  if (i<16) {i++;} else {i=0;}
  
  Serial.print(" A-code: ");  
  for (int j; j<12; j++)    Serial.print(tranTrits_A[j]);
  Serial.print(" B-code: ");
  for (int j; j<12; j++)    Serial.print(tranTrits_B[j]);
  Serial.println(" ");

  Transmitter_A.sendTelegram(tranTrits_A);
  delay(3000);
  Transmitter_B.sendTelegram(tranTrits_B);
  
  
  digitalWrite(LED, LEDstatus);
  LEDstatus = !LEDstatus;
  delay(2000);
}

