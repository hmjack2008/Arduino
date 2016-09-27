
/*
Input
*/

int led_13 = 13;

// the setup routine runs once when you press reset:
void setup() {         

  Serial.begin(9600);
  delay(5000);
  Serial.println("Serial ready");

  
  // initialize the digital pin as an output.
  pinMode(led_13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

}

// the loop routine runs over and over again forever:
void loop() {

  int in_A0 = 0;
  int in_A1 = 0;  
  
  Serial.println("--- serial 0 ---");
  in_A0 = digitalRead(A0);
  in_A1 = analogRead(A1);
  Serial.print(" A0 : "); Serial.println(in_A0);
  Serial.print(" A1 : "); Serial.println(in_A1);

 
  
  delay(1000);  // wait for a second
}
