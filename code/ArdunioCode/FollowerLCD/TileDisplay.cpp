#include "TileDisplay.h"
#include "Color.h"
#include <FastLED.h>

void Tile::Color16BitToRGB (uint16_t color16, unsigned int& r, unsigned int& g, unsigned int& b){
  r = (color16 & 0xF800) >> 11;
  g = (color16 & 0x07E0) >> 5;
  b = color16 & 0x001F;

  r = (r * 255) / 31;
  g = (g * 255) / 63;
  b = (b * 255) / 31;
}

Tile::Tile(LCD* lcd, int num_leds) : lcd_display_{lcd}, num_leds_{num_leds} {
  leds_ = new CRGB[num_leds_];
  FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds_, num_leds_);
  // Clear everything out
  lcd_display_->FillScreen(BLACK);

  for (int i = 0; i < num_leds; i++) {
   leds_[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
}

void Tile::DisplayTile(uint16_t color, int number){
  
  lcd_display_->FillScreen(color);

   unsigned int r, g, b;
   Color16BitToRGB(color, r, g, b);
  
  for (int i = 0; i < num_leds_; i++){
    leds_[i].r = r;
    leds_[i].g = g;
    leds_[i].b = b;
  }
  //brightness 0 - 255
  FastLED.show(50);

  // Number color
  uint16_t num_color = WHITE;
  if (number == 8 || number == 6) {
    num_color = MAGENTA;
  } else if (number > 0){
     lcd_display_->DrawNumCentered(number, num_color);
  }
}

void Tile::DisplayTileNoNumber(uint16_t color){
  lcd_display_->FillScreen(color);
  unsigned int r, g, b;
  Color16BitToRGB(color, r, g, b);
  
  for (int i = 0; i < num_leds_; i++){
    leds_[i].r = r;
    leds_[i].g = g;
    leds_[i].b = b;
  }
  //brightness 0 - 255
  FastLED.show(50);
  
}
