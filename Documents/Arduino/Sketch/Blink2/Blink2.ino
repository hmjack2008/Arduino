
void setup()
{
   Serial.begin(9600);
   delay(4000);
   Serial.println("serial ready");

   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(13, OUTPUT);   
}

void loop()
{
  //digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  //digitalWrite(12, HIGH);
  //digitalWrite(13, HIGH); 
  delayMicroseconds(10);
  //digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  //digitalWrite(12, LOW);
  //digitalWrite(13, LOW);   
  delayMicroseconds(90);

}


