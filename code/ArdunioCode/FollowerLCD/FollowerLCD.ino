#include <SPI.h>

#include "TileDisplay.h"
#include "Organize.h"
#include "Color.h"
#include "Board.h"
#include "TileRunner.h"

#define ROOT_NODE true // this determines if the node is currently the root node

#define NUM_LEDS 12 // Total number of leds in the hexagon
// Note this is just a reminder it is actuall defined in TileDisplay
// #define LEDS_PIN 2

#define DISP_CS 10
#define DISP_RST 7
#define DISP_DC 8
#define DISP_BL 9
// Note this is just a reminder pin 11 and pin 13 are used by the display!
#define NUM_SIDES  6

TileRunner* tr;

void setup() {

  Tile* tile = new Tile(new LCD(DISP_CS, DISP_RST, DISP_DC, DISP_BL, 240, 240, Numbers_Font), NUM_LEDS);
  Board* board = new Board;

  tr = new TileRunner(tile, board);

  // draw out your current tile
  // If root do the first hand off!
  if (ROOT_NODE) {
    delay(100); // just for the asectic
    tr->SetIndex(0);
    tr->DisplayCurrentIndexTile();
    // comunnicate
  }
}

int found_side = 0;
void loop() {
}
