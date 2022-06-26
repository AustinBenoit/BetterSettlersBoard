#include "TileRunner.h"
#include "Color.h"

int TileRunner::GetOutputSide(int input_side){
  // Look at the index and get the correct side to output the power to
  
}

TileRunner::TileRunner(Tile* tile, Board* board) : tile_{tile}, board_{board} {

  int index_ = 0;

  /*for (int i = 0; i < number_sides_; i++) {
     pinMode(output_side_pin_[i], OUTPUT);
     pinMode(input_side_pin_[i], INPUT);
  }*/

  tile_->DisplayTileNoNumber(LIGHTBLUE);
}

void TileRunner::UpdateBoard(int input_pin){

  // ask questions about
  //index
  // side types
  // side nubmers
  // tell it to turn off pin

  // wait for its pin to turn off

  // Set the other side pin high
  // Answer the questions the next node has
  // Turn my pin off when it is happy
  
}

int TileRunner::PollSides() {
  for (int i = 0; i < number_sides_; i++) {
    if (analogRead(input_side_pin_[i]) > 900){ // arbitrary Noise floor should be 1023
      return i;
    }
  }
}

void TileRunner::DisplayCurrentIndexTile(){
  uint16_t color = board_->GetTileColor(index_);
  int num = board_->GetTileNumber(index_);
  Serial.println(color, HEX);

  tile_->DisplayTile(color, num);
}

void TileRunner::SetIndex(int index) {
  index_ = index;
}
