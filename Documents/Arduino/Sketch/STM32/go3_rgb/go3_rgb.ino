
#include <ChainableLED.h>

#define NUM_LEDS  1

ChainableLED leds(PB8, PB9, NUM_LEDS); // clk,dt, #leds

void setup()
{
  leds.init();
}

byte pos = 0;

int i = 0;
void loop()
{
  leds.setColorRGB(0, i, 0, 0);
  delay(100);
  leds.setColorRGB(0, 0, i, 0);
  delay(100);
  leds.setColorRGB(0, 0, 0, i);
  delay(100);
  i = i + 5 ;
  if (i>255) {
    i = 0;
  }
}

