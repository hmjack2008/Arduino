int servo1 = 2; 
 
void setup() {
  
  Serial.begin(9600);
  delay(5000);
  Serial.println("begin");
  pinMode(servo1, INPUT);
  attachInterrupt(0, rc1_begin, RISING);    // catch interrupt 0 (digital pin 2) going HIGH and send to rc1()
 
}
 
 
void rc1_begin() {           // enter rc1_begin when interrupt pin goes HIGH.
 
  detachInterrupt(0);  // after recording the value, detach the interrupt from rc1_begin
  Serial.println("get Int");
  attachInterrupt(0, rc1_begin, RISING); // re-attach the interrupt as rc1_end, so we can record the value when it goes low
 
}

 
void loop() {
  
    Serial.println("Int");
    delay(2000); 
 
}
