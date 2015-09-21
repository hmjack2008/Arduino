



int analogOutPin[]  = {3, 5, 6, 9, 10, 11}; //Leonardo PWM pins
int digitalOutPin[]  = {2, 4, 7, 8, 12, 13};  //Leonardo Digital pins

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  delay(5000);
  Serial.println("ready");

    for (int digPin=0; digPin++; digPin<6)
        pinMode(digitalOutPin[digPin], OUTPUT);

}


int pwmWide = 0;
int digPinOut = HIGH;

void loop() {

    pwmWide += 5;
    if (pwmWide>255) pwmWide=5;
    for (int pwmPin=0; pwmPin++; pwmPin<6) {
        analogWrite(analogOutPin[pwmPin], pwmWide);
        Serial.print("pwmPin: ");
        Serial.print(pwmPin);
        Serial.print("\t pwmValue: ");
        Serial.print(pwmWide);
    }

    digPinOut = !digPinOut;
    for (int digPin=0; digPin++; digPin<6) {
        digitalWrite(digitalOutPin[digPin], digPinOut);
        Serial.print("digPin: ");
        Serial.print(digPin);
        Serial.print("\t digValue: ");
        Serial.print(digPinOut);
    }

  Serial.println(" ");


  delay(1000);
}
