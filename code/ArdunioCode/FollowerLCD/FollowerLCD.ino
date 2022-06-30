#include "TileDisplay.h"
#include "Color.h"
#include "Board.h"
#include "TileRunner.h"

#define ROOT_NODE false // this determines if the node is currently the root node

#define NUM_LEDS 12 // Total number of leds in the hexagon
// Note this is just a reminder it is actuall defined in TileDisplay
// #define LEDS_PIN 2

#define DISP_CS 10
#define DISP_RST 7
#define DISP_DC 8

// Note this is just a reminder pin 11 and pin 13 are used by the display!
#define NUM_SIDES  6

int output_side_pin[6] = {3, 4, 5, 6, 9, 12}; 
int input_side_pin[6] = {A0, A1, A2, A3, A6, A7};

TileRunner* tr;

void setup() {
  // If anything need randomness
  randomSeed(analogRead(A0));
  Tile* tile = new Tile(new LCD(DISP_CS, DISP_RST, DISP_DC, 240, 240, Numbers_Font), NUM_LEDS);
  Board* board = new Board;
  tr = new TileRunner(tile, board, output_side_pin, input_side_pin);
  // If root do the first hand off!
  if (ROOT_NODE) {
    tr->SetIndex(0);
    tr->DisplayCurrentIndexTile();
    // Probably a much better way to do all of this
    // But the send board will start off using pin 4.
    // the first side (or sides[0]) will be set to an interupt that uses pin 3;
    // configure the board rest pin
    // This will restart the whole algorithum


    // Now send the board using the only real output side.
    tr->SendBoard(1); 
    tr->ConfigureRestBoard(3);
  }
}

int found_side = 0;
void loop() {

  if (ROOT_NODE) {
    if (tr->send_new_board_) {
      tr->DisplayCurrentIndexTile();
      tr->send_new_board_ = false;
      tr->SendBoard(1); 
    }
  } else {
    Serial.println("Looking for pins");
    // wait for side to be high indicating a new board;
    found_side = tr->PollSides();
    if (found_side != -1) {
      Serial.print("Found Pin ");
      Serial.println(found_side);
      tr->UpdateBoard();
      Serial.print("Next Side: ");
      int next_side = tr->GetNextOutputSide(found_side);
      Serial.println(next_side);
      tr->SerialPrintBoard();
      // don't try and send after last tile
      // Currently only have 3 working boards
      // TODO when I have more boards then set this base on the number of tiles in the board class. 
      if (tr->GetIndex() < 2){
        tr->SendBoard(next_side);
      }
      tr->DisplayCurrentIndexTile();
    }
  delay(100);
  }
}
