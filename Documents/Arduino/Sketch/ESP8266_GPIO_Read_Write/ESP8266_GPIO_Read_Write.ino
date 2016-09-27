
/*

connect GPIO-0 to GPIO-2 for this program.

*/

int p_GPIO0 = 0;
int p_GPIO2 = 2;
int s_GPIO0 = LOW;
int s_GPIO2 = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(p_GPIO0, INPUT);
  pinMode(p_GPIO2, OUTPUT);
//  analogWrite(p_GPIO2, 127); //set GPIO-2 to PWM(2ms) 50%
}

void loop() {
  
  digitalWrite(p_GPIO2, s_GPIO2 = !s_GPIO2); // set and change the GPIO-2
  Serial.print("set GPIO 2 : ");            // print the status of GPIO-2
  Serial.println(s_GPIO2);
  
  s_GPIO0 = digitalRead(p_GPIO0);            // get GPIO-0
  Serial.print("get GPIO 0 : ");            // print the status of GPIO-0
  Serial.println(s_GPIO0);
  
  delay(2000);
}
