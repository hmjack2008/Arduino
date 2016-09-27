void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200); // PA3:Rx  PA2:Tx
  Serial2.begin(115200); // PB11:Rx  PB10:Tx
  Serial.begin(115200); // PA9:Rx  PA10:Tx
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.println("Serial 1");
  Serial2.println("Serial 2");
  Serial.println("Serial 0");
  delay(2000);
}
