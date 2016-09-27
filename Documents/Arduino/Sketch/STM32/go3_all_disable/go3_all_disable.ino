void setup() {
  // put your setup code here, to run once:
  pinMode(PA0,INPUT);   // A0
  pinMode(PA1,INPUT);   // A1
  pinMode(PA2,INPUT);   // ~Tx
  pinMode(PA3,INPUT);   // ~Rx
  pinMode(PA4,INPUT);   // A2
  pinMode(PA5,INPUT);   // D13(SCK) ; A5
  pinMode(PA6,INPUT);   // D12(MISO)
  pinMode(PA7,INPUT);   // D11(MOSI)
  pinMode(PA8,INPUT);   // D7
  pinMode(PA9,INPUT);   // ~CP_Rx
  pinMode(PA10,INPUT);  // ~CP_Tx
  pinMode(PA11,INPUT);  // OTG_DM
  pinMode(PA12,INPUT);  // OTG_DP
  pinMode(PA13,INPUT);  // SWDIO
  pinMode(PA14,INPUT);  // SWCLK
  pinMode(PA15,INPUT);  // D10(CS)
  pinMode(PB0,INPUT);   // A3
  pinMode(PB1,INPUT);   // LED3 ; A4
  pinMode(PB2,INPUT);   // Boot1
  pinMode(PB3,INPUT);   // D3
  pinMode(PB4,INPUT);   // D5
  pinMode(PB5,INPUT);   // D4
  pinMode(PB6,INPUT);   // D8
  pinMode(PB7,INPUT);   // D2
  pinMode(PB8,OUTPUT_OPEN_DRAIN); // SCL
  pinMode(PB9,OUTPUT_OPEN_DRAIN); // SDA
  pinMode(PB10,INPUT);   // D6
  pinMode(PB11,INPUT);   // LED3 ; D9
  pinMode(PB12,INPUT);   // (CS)
  pinMode(PB13,INPUT);   // SCK
  pinMode(PB14,INPUT);   // LED2 ; MISO
  pinMode(PB15,OUTPUT);  // LED1 ; MOSI
  pinMode(PC13,INPUT);   // NA
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PB15,HIGH);
  delay(1000);
  digitalWrite(PB15,LOW);
  delay(1000);  
}
