#include <MotorDC.h>

MotorDC motorDC(PB4, PB5);

void setup()
{
  motorDC.setSpeed(0);
  Serial.begin(9600);
  delay(5000);
  Serial.println("Motor DC Library");
}

void loop()
{
  // PWM 0 to 255
  Serial.println("1. Motor DC +");
  motorDC.setSpeed(15); // +255 ~ 0 ~ -255
  delay(100);
  
  // Stop
  Serial.println("2. Motor DC STOP");
  motorDC.setSpeed(0);
  delay(1000);
  
  // PWM -255 to 0
  Serial.println("3. Motor DC -");
  Serial.println("3.1");
  motorDC.setSpeed(-15); // +255 ~ 0 ~ -255
  Serial.println("3.2");
  delay(100);
  Serial.println("3.3");
  
  // Stop
  Serial.println("4. Motor DC STOP");
  motorDC.setSpeed(0);
  delay(1000);

  delay(3000);
}
