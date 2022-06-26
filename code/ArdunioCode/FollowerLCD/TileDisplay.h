#ifndef TILEDISPLAY_H
#define TILEDISPLAY_H

#include "LCD_Display.h"
#include <FastLED.h>

#define LEDS_PIN 3

class Tile {
private:
  LCD* lcd_display_;
  CRGB* leds_;
  int num_leds_;
  void Color16BitToRGB (uint16_t color16, unsigned int& r, unsigned int& g, unsigned int& b);
public:
  Tile(LCD* lcd, int num_leds);
  void DisplayTile(uint16_t color, int number);
  void DisplayTileNoNumber(uint16_t color);
};


#endif //TILEDISPLAY_H
