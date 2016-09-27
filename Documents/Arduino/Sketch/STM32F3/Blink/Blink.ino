int led[] = {PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15};
int led_size = 8;
void setup() {         
  for (int i=0; i<led_size; i++)  pinMode(led[i], OUTPUT);
}
void loop() {
  for (int i=0; i<led_size; i++)  digitalWrite(led[i], HIGH);
  delay(200);
  for (int i=0; i<led_size; i++)  digitalWrite(led[i], LOW);
  delay(200);
}
