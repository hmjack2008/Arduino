
int PWMs[] = {PA0,PA1,PA2,PA3, PA6,PA7, PA8,PA9,PA10,PA11, PB0,PB1, PB6,PB7,PB8,PB9};
int iPWM = 16;
int ADCs[] = {PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7, PB0,PB1};
int iADC = 10;
int iPIN = 32;
int iDuty = 0;
int iCount = 0;
int vADC = 0;

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Serial 0 begin ...");
  for (int iCount=0; iCount<iADC; iCount++) {
    pinMode(ADCs[iCount], INPUT);
  }
}

void loop() {
  Serial.println("--Scan ADC--");
  for (int iCount=0; iCount<iADC; iCount++) {
    vADC = analogRead(ADCs[iCount]);
	Serial.print(iCount);
	Serial.print(" / ");
  Serial.print(ADCs[iCount]);
  Serial.print(" : ");
	Serial.print(vADC);
	Serial.println("");
	delay(20);
  }
  
  Serial.println("--Scan End--");
  delay(2000);
}
