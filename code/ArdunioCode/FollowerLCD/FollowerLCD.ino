#include <SPI.h>
#include "LCD_Display.h"
#include <FastLED.h>
#include "color.h"

#define NUM_LEDS 4

LCD* disp;

CRGB leds[NUM_LEDS];

void setup()
{
  disp = new LCD(10, 7, 8, 9, 240, 240, Numbers_Font);
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);

}


void loop()
{
  for (int i = 1; i < 100; i++) {
    disp->FillScreen(GRAY);
    disp->DrawNumCentered(i, BLACK);
    delay(100);
    
  }
  
  leds[0] = CHSV(214, 125, 100);
  leds[1] = CHSV(214, 125, 100);
  leds[2] = CHSV(214, 125, 100);
  leds[3] = CHSV(214, 125, 100); FastLED.show();
  
}
