int _ABVAR_1_loop_count = 0 ;
void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

int _ABVAR_2_led_pwm = 0 ;

void setup()
{
  Serial.begin(9600);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  _ABVAR_1_loop_count = 0 ;

}

void loop()
{
  _ABVAR_1_loop_count = ( _ABVAR_1_loop_count + 1 ) ;
  Serial.print("Loop");
  Serial.print(" ");
  Serial.print(_ABVAR_1_loop_count);
  Serial.print(" ");
  Serial.println();
  Serial.print("Time");
  Serial.print(" ");
  Serial.print(millis());
  Serial.print(" ");
  Serial.println();
  __ardublockDigitalWrite(13, HIGH);
  delay( 500 );
  __ardublockDigitalWrite(13, LOW);
  delay( 500 );
  for (_ABVAR_2_led_pwm= 1; _ABVAR_2_led_pwm<= ( 255 ); _ABVAR_2_led_pwm++ )
  {
    _ABVAR_2_led_pwm = ( _ABVAR_2_led_pwm + 1 ) ;
    analogWrite(5 , _ABVAR_2_led_pwm);
    analogWrite(6 , ( 255 - _ABVAR_2_led_pwm ));
    delay( 20 );
  }
  Serial.print("input:");
  Serial.print(" ");
  Serial.println();
}


