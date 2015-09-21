void writeMotors() { // [1000;2000] => [125;250]
  #if defined(MEGA)
    for(uint8_t i=0;i<NUMBER_MOTOR;i++)
      analogWrite(PWM_PIN[i], motor[i]/4-250);
  #else
    for(uint8_t i=0;i<min(NUMBER_MOTOR,4);i++)
      analogWrite(PWM_PIN[i], motor[i]/4-250);
    #if (NUMBER_MOTOR == 6)
      atomicPWM_PIN5_highState = motor[5]/4-250;
      atomicPWM_PIN5_lowState = 255-atomicPWM_PIN5_highState;
      atomicPWM_PIN6_highState = motor[4]/4-250;
      atomicPWM_PIN6_lowState = 255-atomicPWM_PIN6_highState;
    #endif
  #endif
  #if defined(PROMINI)
    for(uint8_t i=0;i<NUMBER_MOTOR;i++)
      analogWrite(PWM_PIN[i], motor[i]/4-250);
  #else
    for(uint8_t i=0;i<min(NUMBER_MOTOR,4);i++)
      analogWrite(PWM_PIN[i], motor[i]/4-250);
    #if (NUMBER_MOTOR == 6)
      atomicPWM_PIN5_highState = motor[5]/4-250;
      atomicPWM_PIN5_lowState = 255-atomicPWM_PIN5_highState;
      atomicPWM_PIN6_highState = motor[4]/4-250;
      atomicPWM_PIN6_lowState = 255-atomicPWM_PIN6_highState;
    #endif
  #endif
}
