
int PWMs[] = {PA0,PA1,PA2,PA3, PA6,PA7, PA8,PA9,PA10,PA11, PB0,PB1, PB6,PB7,PB8,PB9};
int iPWM = 16;
int iDuty = 0;
int iCount = 0;

void setup() {

}

void loop() {

  for (int iCount=0; iCount<iPWM; iCount++) {
    analogWrite(PWMs[iCount], iDuty);
  }

  iDuty = iDuty + 5;
  if (iDuty>255) {
    iDuty = 0;
  }
  
  delay(100);
}
