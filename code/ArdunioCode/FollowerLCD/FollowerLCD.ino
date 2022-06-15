#include <SPI.h>

#include "TileDisplay.h"
#include "BoardSetUp.h"
#include "Color.h"

#define NUM_LEDS 12 // Total number of leds in the hexagon
// Note this is just a reminder it is actuall defined in TileDisplay
// #define LEDS_PIN 3

#define DISP_CS 10
#define DISP_RST 7
#define DISP_DC 8
#define DISP_BL 9
// Note this is just a reminder pin 11 and pin 13 are used by the display!

Tile* tile;

void setup() {
   tile = new Tile(new LCD(DISP_CS, DISP_RST, DISP_DC, DISP_BL, 240, 240, Numbers_Font), NUM_LEDS);


  // If leader then kick off 

}


void loop() {
  pinMode(12, OUTPUT);
  for (int i = 2; i < 13; i++) {
    delay(500);
    tile->DisplayTile(RED, i);
  } 
}
