
int LEDs[] = {PB15, PB14, PB11 ,PB1}; // GD32
// int LEDs[] = {PA8}; // MM32
int LEDsize = 4;

void setup() {
  for (int i=0; i<LEDsize; i++) {
    pinMode(LEDs[i],OUTPUT);
  }
}

void loop() {
  for (int i=0; i<LEDsize; i++) {
    digitalWrite(LEDs[i],HIGH);
    delay(400);
    digitalWrite(LEDs[i],LOW);
    delay(100);
  }
}
