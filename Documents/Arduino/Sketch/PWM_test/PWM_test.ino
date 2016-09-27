
int analogOutPin[]  = {3, 5, 6, 9, 10, 11}; //Leonardo PWM pins
int digitalOutPin[]  = {2, 4, 7, 8, 12, 13};  //Leonardo Digital pins

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  delay(3000);
  Serial.println("ready");
}

int pwmWide = 0;
int digPinOut = HIGH;

void loop() {

    pwmWide += 3;
    if (pwmWide>255) pwmWide=5;
    
    for (int pwmPin=0; pwmPin<6; pwmPin++) {
        analogWrite(analogOutPin[pwmPin], pwmWide);
        
        Serial.print("pwmPin: ");
        Serial.print(pwmPin);
        Serial.print("\t pwmValue: ");
        Serial.print(pwmWide);
    }

  Serial.println(" ! ");

  delay(500);
}
