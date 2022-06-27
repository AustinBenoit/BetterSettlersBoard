#include "TileDisplay.h"
#include "Color.h"
#include "Board.h"
#include "TileRunner.h"

#define ROOT_NODE false// this determines if the node is currently the root node

#define NUM_LEDS 12 // Total number of leds in the hexagon
// Note this is just a reminder it is actuall defined in TileDisplay
// #define LEDS_PIN 2

#define DISP_CS 10
#define DISP_RST 7
#define DISP_DC 8

// Note this is just a reminder pin 11 and pin 13 are used by the display!
#define NUM_SIDES  6

TileRunner* tr;

void setup() {
  Tile* tile = new Tile(new LCD(DISP_CS, DISP_RST, DISP_DC, 240, 240, Numbers_Font), NUM_LEDS);
  Board* board = new Board;

  tr = new TileRunner(tile, board);

  // If root do the first hand off!
  if (ROOT_NODE) {
    //delay(5000); // just for the asectic
    tr->SetIndex(0);
    tr->DisplayCurrentIndexTile();
    tr->SendBoard(0);
    // comunnicate
  }
}

int found_side = 0;
void loop() {

  if (ROOT_NODE) {
    //wait for reset
    Serial.println("Master Done");
    
  } else {
    Serial.println("Looking for pins");
    // wait for side to be high indicating a new board;
    found_side = tr->PollSides();
    if (found_side != -1) {
      Serial.print("Found Pin");
      Serial.print(found_side);
      tr->UpdateBoard(found_side);
    }
    delay(100);
  }
}
