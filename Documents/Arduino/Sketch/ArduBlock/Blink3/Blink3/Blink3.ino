boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}


void setup()
{
}

void loop()
{
  if (__ardublockDigitalRead(3))
  {
    __ardublockDigitalWrite(13, HIGH);
  }
  else
  {
    __ardublockDigitalWrite(13, LOW);
  }
}


