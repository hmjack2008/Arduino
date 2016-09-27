
#define _CDS 3 // Output, Hi: Enable; Low: Disable
#define _OUT 2 // Input, Hi: Found

#define led_13 13

int getMesg = 0;
void getMessage(void)
{
    // noInterrupts();
    getMesg = 1;
    // interrupts();
}

void setup() {         
  Serial.begin(9600);
  delay(4000);
  Serial.println("Serial ready");
  delay(1000);
  
  // initialize the digital pin as an output.
  pinMode(led_13, OUTPUT);
  pinMode(_CDS, OUTPUT);
  pinMode(_OUT, INPUT);
  
  digitalWrite(_CDS, HIGH); 
  attachInterrupt(0, getMessage, RISING); // set interrupt 0 : pin-2, 
/*
LOW 当引脚为低电平时，触发中断
CHANGE 当引脚电平发生改变时，触发中断
RISING 当引脚由低电平变为高电平时，触发中断
FALLING 当引脚由高电平变为低电平时，触发中断.
 */
}

void loop() {
  if ( getMesg )
  {
    Serial.println(" --- FOUND --- ");
    getMesg = 0;
  }
  digitalWrite(led_13, HIGH);
  delay(200);
  digitalWrite(led_13, LOW);
  delay(200);
}
