#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <stdint.h>
#include <stdio.h>
#include <SPI.h>
#include <avr/pgmspace.h>
#include "font.h"

class LCD {
private:
  int cs_pin_, dc_pin_, rst_pin_, bl_pin_;
  int height_, width_;
  int bl_brightness = 140;
  const NumberFont* font_;

  void ConfigureGPIO();
  void ConfigureComunication();
  void ConfigureScreen();

  void WriteData(uint8_t data); 
  void WriteData(uint16_t data);
  void WriteReg(uint8_t reg); 

  void SetCursor(uint8_t x1, uint8_t y1, uint8_t x2,uint8_t y2);
  void SetPixelColor(uint8_t x, uint8_t y, uint16_t Color);
  void ResetScreen();

public:
  LCD (int cs, int dc, int st, int bl, int height, int width, const NumberFont* font);
  
  void ClearScreen();
  
  void DrawPixel(uint16_t x_point, uint16_t y_point, uint16_t color);
  /* DrawNum
   * Draws one number anywhere on the screen.
   */
  void DrawNum(uint16_t x_point, uint16_t y_point, int num, uint16_t color);
  
  /* DrawNumCentered
   * Draws up to two numbers centered on the screen.
   * This enables easy setup of the catan board.
   */
  void DrawNumCentered(int num, uint16_t color);
  void FillScreen(uint16_t color);
};

#endif //LCD_DISPLAY_H
