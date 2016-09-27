void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

int i=0;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,HIGH);
  
    analogWrite(4,i);
    analogWrite(9,i);
    analogWrite(10,i);
    analogWrite(11,i);
    delay(500);
    
  if (i<64) i++; else i=0;  
  
  delay(200);
  digitalWrite(13,LOW);
  delay(300);
  
}
