#include "TileRunner.h"
#include "Color.h"
#include "Wire.h"

int TileRunner::index_;
bool TileRunner::sending_data_;
Board* TileRunner::board_;

int TileRunner::GetNextOutputSide(int input_side){
  // Look at the index and get the correct side to output the power to
  
}

TileRunner::TileRunner(Tile* tile, Board* board) {
  board_ = board;
  TileRunner::tile_ = tile;
  TileRunner::index_ = 0;

  for (int i = 0; i < number_sides_; i++) {
     pinMode(TileRunner::output_side_pin_[i], OUTPUT);
     pinMode(TileRunner::input_side_pin_[i], INPUT);
  }

  TileRunner::tile_->DisplayTileNoNumber(LIGHTBLUE);
}

void TileRunner::UpdateBoard(int input_pin){

  

  // ask questions about.
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
  int index = index_;
  uint16_t color = board_->GetTileColor(index_);
  int num = board_->GetTileNumber(index_);
  tile_->DisplayTile(color, num);
}

void TileRunner::SetIndex(int index) {
  index_ = index;
}

void TileRunner::SendBoard(int side){

  Wire.begin(50); // join i2c bus
  sending_data_ = true;
  Wire.onReceive(SendOnReceiveController);
  Wire.onRequest(SendOnRequestIndex);

  digitalWrite(side, HIGH);
  
  // sending_data will be set to false by a 
  // side effect of SendOndReceive Controller
  while (sending_data_) {
    //nop
  }

  Wire.end();
  // set pin to low
  digitalWrite(side, LOW);
}


void TileRunner::SendOnReceiveController(int how_many){
  if( Wire.available()) {
      byte input = Wire.read(); // receive byte as a character
      if (input == byte(1)) { // Give back the index
        Serial.println("Gvie back index");
        Wire.onRequest(SendOnRequestIndex);
        return;
        
      } else if (input == byte(2)) { // Give Back the types
        Wire.onRequest(SendOnRequestTileTypes);
        return;
        
      } else if (input == byte(3)) { // Give back the numbers
        Wire.onRequest(SendOnRequestTileNumbers);
        return;
        
      } else if (input == byte(4)) {
        sending_data_ = false;
        return;
      }
      return;
  }
} 

void TileRunner::SendOnRequestIndex(){
    Wire.write(index_ + 1);
}

void TileRunner::SendOnRequestTileTypes() {
  for (int i = 0; i < board_->number_tiles_; i++) {
    Wire.write(board_->GetTileType(i));
  }
}
  
void TileRunner::SendOnRequestTileNumbers(){
  for (int i = 0; i < board_->number_tiles_; i++) {
    Wire.write(board_->GetTileNumber(i));
  }
}
