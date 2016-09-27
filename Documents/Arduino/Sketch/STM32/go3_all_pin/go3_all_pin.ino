void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(5000);
  Serial.println("begin ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(" === boardADCPins === ");

  for (uint32 i = 0; i < BOARD_NR_ADC_PINS; i++) {
    Serial.print(" ");
    Serial.print(boardADCPins[i]);
  }
  Serial.println("");
  
  Serial.println(" === boardPWMPins === ");  
  for (uint32 j = 0; j < BOARD_NR_PWM_PINS; j++) {
    Serial.print(" ");
    Serial.print(boardPWMPins[j]);
  }
  Serial.println("");

  Serial.println(" === boardPins === ");
  Serial.print("PA 0-15: "); Serial.print(PA0);
  Serial.print(" , "); Serial.print(PA1);
  Serial.print(" , "); Serial.print(PA2);
  Serial.print(" , "); Serial.print(PA3);
  Serial.print(" , "); Serial.print(PA4);
  Serial.print(" , "); Serial.print(PA5);
  Serial.print(" , "); Serial.print(PA6);
  Serial.print(" , "); Serial.print(PA7);
  Serial.print(" , "); Serial.print(PA8);
  Serial.print(" , "); Serial.print(PA9);
  Serial.print(" , "); Serial.print(PA10);
  Serial.print(" , "); Serial.print(PA11);
  Serial.print(" , "); Serial.print(PA12);
  Serial.print(" , "); Serial.print(PA13);
  Serial.print(" , "); Serial.print(PA14);
  Serial.print(" , "); Serial.println(PA15);  
  Serial.print("PB 0-15: "); Serial.print(PB0);
  Serial.print(" , "); Serial.print(PB1);
  Serial.print(" , "); Serial.print(PB2);
  Serial.print(" , "); Serial.print(PB3);
  Serial.print(" , "); Serial.print(PB4);
  Serial.print(" , "); Serial.print(PB5);
  Serial.print(" , "); Serial.print(PB6);
  Serial.print(" , "); Serial.print(PB7);
  Serial.print(" , "); Serial.print(PB8);
  Serial.print(" , "); Serial.print(PB9);
  Serial.print(" , "); Serial.print(PB10);
  Serial.print(" , "); Serial.print(PB11);
  Serial.print(" , "); Serial.print(PB12);
  Serial.print(" , "); Serial.print(PB13);
  Serial.print(" , "); Serial.print(PB14);
  Serial.print(" , "); Serial.println(PB15);    


  delay(3000);
}
