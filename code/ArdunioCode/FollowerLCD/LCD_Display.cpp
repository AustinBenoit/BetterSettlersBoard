#include "LCD_Display.h"
#include "font.h"
#include "Color.h"

LCD::LCD(int cs, int dc, int rst, int height, int width, const NumberFont* font) : cs_pin_{cs}, dc_pin_{dc}, rst_pin_{rst}, height_{height}, width_{width} {
  font_ = font;
  ConfigureGPIO();
  ConfigureComunication();
  ConfigureScreen();
  FillScreen(BLACK);
}

void LCD::ConfigureGPIO(){
  pinMode(cs_pin_, OUTPUT);
  pinMode(rst_pin_, OUTPUT);
  pinMode(dc_pin_, OUTPUT);
}

void LCD::ConfigureComunication(){
  //Serial
  Serial.begin(115200);
  
  //spi
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
}

void LCD::ConfigureScreen() {

  // Prep screen
  digitalWrite(cs_pin_, LOW);
  delay(100);
  digitalWrite(rst_pin_, LOW);;
  delay(100);
  digitalWrite(rst_pin_, HIGH);
  delay(100);

 
  WriteReg(0xEF);
  WriteReg(0xEB);
  WriteData( (uint8_t) 0x14); 
  
  WriteReg(0xFE);      
  WriteReg(0xEF); 

  WriteReg(0xEB); 
  WriteData((uint8_t)0x14); 

  WriteReg(0x84);     
  WriteData((uint8_t)0x40); 

  WriteReg(0x85);     
  WriteData((uint8_t)0xFF); 

  WriteReg(0x86);     
  WriteData((uint8_t)0xFF); 

  WriteReg(0x87);     
  WriteData((uint8_t)0xFF);

  WriteReg(0x88);     
  WriteData((uint8_t)0x0A);

  WriteReg(0x89);     
  WriteData((uint8_t)0x21); 

  WriteReg(0x8A);     
  WriteData((uint8_t)0x00); 

  WriteReg(0x8B);     
  WriteData((uint8_t)0x80); 

  WriteReg(0x8C);     
  WriteData((uint8_t)0x01); 

  WriteReg(0x8D);     
  WriteData((uint8_t)0x01); 

  WriteReg(0x8E);     
  WriteData((uint8_t)0xFF); 

  WriteReg(0x8F);     
  WriteData((uint8_t)0xFF); 


  WriteReg(0xB6);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x20);

  WriteReg(0x36);
  WriteData((uint8_t)0x08);

  WriteReg(0x3A);     
  WriteData((uint8_t)0x05); 


  WriteReg(0x90);     
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x08); 

  WriteReg(0xBD);     
  WriteData((uint8_t)0x06);
  
  WriteReg(0xBC);     
  WriteData((uint8_t)0x00); 

  WriteReg(0xFF);     
  WriteData((uint8_t)0x60);
  WriteData((uint8_t)0x01);
  WriteData((uint8_t)0x04);

  WriteReg(0xC3);     
  WriteData((uint8_t)0x13);
  WriteReg(0xC4);     
  WriteData((uint8_t)0x13);

  WriteReg(0xC9);     
  WriteData((uint8_t)0x22);

  WriteReg(0xBE);     
  WriteData((uint8_t)0x11); 

  WriteReg(0xE1);     
  WriteData((uint8_t)0x10);
  WriteData((uint8_t)0x0E);

  WriteReg(0xDF);     
  WriteData((uint8_t)0x21);
  WriteData((uint8_t)0x0c);
  WriteData((uint8_t)0x02);

  WriteReg(0xF0);   
  WriteData((uint8_t)0x45);
  WriteData((uint8_t)0x09);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x26);
  WriteData((uint8_t)0x2A);

  WriteReg(0xF1);    
  WriteData((uint8_t)0x43);
  WriteData((uint8_t)0x70);
  WriteData((uint8_t)0x72);
  WriteData((uint8_t)0x36);
  WriteData((uint8_t)0x37);  
  WriteData((uint8_t)0x6F);


  WriteReg(0xF2);   
  WriteData((uint8_t)0x45);
  WriteData((uint8_t)0x09);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x26);
  WriteData((uint8_t)0x2A);

  WriteReg(0xF3);   
  WriteData((uint8_t)0x43);
  WriteData((uint8_t)0x70);
  WriteData((uint8_t)0x72);
  WriteData((uint8_t)0x36);
  WriteData((uint8_t)0x37); 
  WriteData((uint8_t)0x6F);

  WriteReg(0xED); 
  WriteData((uint8_t)0x1B); 
  WriteData((uint8_t)0x0B); 

  WriteReg(0xAE);     
  WriteData((uint8_t)0x77);
  
  WriteReg(0xCD);     
  WriteData((uint8_t)0x63);   


  WriteReg(0x70);     
  WriteData((uint8_t)0x07);
  WriteData((uint8_t)0x07);
  WriteData((uint8_t)0x04);
  WriteData((uint8_t)0x0E); 
  WriteData((uint8_t)0x0F); 
  WriteData((uint8_t)0x09);
  WriteData((uint8_t)0x07);
  WriteData((uint8_t)0x08);
  WriteData((uint8_t)0x03);

  WriteReg(0xE8);     
  WriteData((uint8_t)0x34);

  WriteReg(0x62);     
  WriteData((uint8_t)0x18);
  WriteData((uint8_t)0x0D);
  WriteData((uint8_t)0x71);
  WriteData((uint8_t)0xED);
  WriteData((uint8_t)0x70); 
  WriteData((uint8_t)0x70);
  WriteData((uint8_t)0x18);
  WriteData((uint8_t)0x0F);
  WriteData((uint8_t)0x71);
  WriteData((uint8_t) 0xEF);
  WriteData((uint8_t)0x70); 
  WriteData((uint8_t)0x70);

  WriteReg(0x63);     
  WriteData((uint8_t)0x18);
  WriteData((uint8_t)0x11);
  WriteData((uint8_t)0x71);
  WriteData((uint8_t)0xF1);
  WriteData((uint8_t)0x70); 
  WriteData((uint8_t)0x70);
  WriteData((uint8_t)0x18);
  WriteData((uint8_t)0x13);
  WriteData((uint8_t)0x71);
  WriteData((uint8_t)0xF3);
  WriteData((uint8_t)0x70); 
  WriteData((uint8_t)0x70);

  WriteReg(0x64);     
  WriteData((uint8_t)0x28);
  WriteData((uint8_t)0x29);
  WriteData((uint8_t)0xF1);
  WriteData((uint8_t)0x01);
  WriteData((uint8_t)0xF1);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x07);

  WriteReg(0x66);     
  WriteData((uint8_t)0x3C);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0xCD);
  WriteData((uint8_t)0x67);
  WriteData((uint8_t)0x45);
  WriteData((uint8_t)0x45);
  WriteData((uint8_t)0x10);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x00);

  WriteReg(0x67);     
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x3C);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x00);
  WriteData((uint8_t)0x01);
  WriteData((uint8_t)0x54);
  WriteData((uint8_t)0x10);
  WriteData((uint8_t)0x32);
  WriteData((uint8_t)0x98);

  WriteReg(0x74);     
  WriteData((uint8_t)0x10); 
  WriteData((uint8_t)0x85); 
  WriteData((uint8_t)0x80);
  WriteData((uint8_t)0x00); 
  WriteData((uint8_t)0x00); 
  WriteData((uint8_t)0x4E);
  WriteData((uint8_t)0x00);         
  
  WriteReg(0x98);     
  WriteData((uint8_t)0x3e);
  WriteData((uint8_t)0x07);

  WriteReg(0x35); 
  WriteReg(0x21);

  WriteReg(0x11);
  delay(120);
  WriteReg(0x29);
  delay(20);
}

void LCD::SetCursor(uint8_t x1, uint8_t y1, uint8_t x2,uint8_t y2) {
  WriteReg(0x2a);
  WriteData((uint8_t)0x00);
  WriteData(x1);
  WriteData((uint8_t)0x00);  
  WriteData(x2);
  
  WriteReg(0x2b);
  WriteData((uint8_t)0x00);
  WriteData(y1);
  WriteData((uint8_t)0x00);
  WriteData(y2);
  
  WriteReg(0x2c);
}

void LCD::SetPixelColor(uint8_t x, uint8_t y, uint16_t color) {
  SetCursor(x,y,x,y);
  WriteData(color);
}

void LCD::WriteData(uint8_t data) 
{ 
  digitalWrite(cs_pin_, LOW);
  digitalWrite(dc_pin_, HIGH);
  SPI.transfer(data);
  digitalWrite(cs_pin_, HIGH);
}  

void LCD::WriteData(uint16_t data)
{
  digitalWrite(cs_pin_, LOW);
  digitalWrite(dc_pin_, HIGH);
  SPI.transfer(data>>8);
  SPI.transfer(data);
  digitalWrite(cs_pin_, HIGH);
}   

void LCD::WriteReg(uint8_t data)  
{ 
  digitalWrite(cs_pin_, LOW);
  digitalWrite(dc_pin_, LOW);
  SPI.transfer(data);
}

void LCD::DrawPixel(uint16_t x_point, uint16_t Y_point, uint16_t color) {
  SetPixelColor(x_point, Y_point, color);
}

/* DrawNum
 *  Draws a number on the screen at the specific point.
 *  Only draws a single digit.
 */
void LCD::DrawNum(uint16_t x_point, uint16_t y_point, int num, uint16_t color) {

  if ( 0 > num || num > 9 ){
    return;
  }
  
  int font_width = font_[num].width; 
  int font_height = font_[num].height;
  const unsigned char *ptr = font_[num].bitArray;
  for ( int page = 0; page < font_height; page ++ ) {
    for ( int column = 0; column < font_width; column ++ ) {
        if (pgm_read_byte(ptr) & (0x80 >> (column % 8)))
          DrawPixel (x_point + column, y_point + page, color);
      
      //One pixel is 8 bits
      if (column % 8 == 7) {
        ptr++;
      }
    }/* Write a line */
    if (font_width % 8 != 0) {
      ptr++;
    }
  }
}

void LCD::DrawNumCentered(int num, uint16_t color) {
  if (0 > num || num > 99) {
    return;
  }

  if (num > 9){
    int ones = num % 10;
    int tens = num / 10;
    int width_ones = font_[ones].width;
    int height_ones = font_[ones].height;
    int width_tens = font_[tens].width;
    int height_tens = font_[tens].height;

    int width = (width_ - width_ones - width_tens)/2;
    int height = (height_ - max(height_ones, height_tens)) / 2;

    DrawNum(width, height, tens, color);
    DrawNum(width + width_tens, height, ones, color);
    
  } else {
    int height = (height_ - font_[num].height)/2;
    int width = (width_ - font_[num].width)/2;
    DrawNum(width, height, num, color);
  }

}

void LCD::FillScreen(uint16_t color){   
  SetCursor(0, 0, width_- 1,height_ - 1);
  for(int i = 0; i < width_; i++){
    for(int j = 0; j < height_; j++){
      WriteData(color);
    }
  }
}
