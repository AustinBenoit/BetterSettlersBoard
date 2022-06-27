#include "TileRunner.h"
#include "Color.h"
#include "Wire.h"

int TileRunner::index_;
volatile bool TileRunner::sending_data_; 
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
  Wire.begin(getting_board_addr_);// join i2c
  
  Wire.beginTransmission(sending_board_addr_); // ask the sender
  Wire.write(byte(1)); // get index
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(sending_board_addr_, 1); // TODO define numb bytes better
  
  SetIndex(Wire.read());

  Wire.beginTransmission(sending_board_addr_); // ask the sender
  Wire.write(byte(2)); // get tile types
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(sending_board_addr_, 19); // TODO define numb bytes better

  //TODO this is very fragile perhaps need to make it better?
  for (int i = 0; i <  board_->number_tiles_; i++) { // does this need to be < 1??
    board_->SetTileType(i, (TileType)Wire.read());
  }

  Wire.beginTransmission(sending_board_addr_); // ask the sender
  Wire.write(byte(3)); // get tile numbers
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(sending_board_addr_, 19); // TODO define numb bytes better

  //TODO this is very fragile perhaps need to make it better?
  for (int i = 0; i <  board_->number_tiles_; i++) { // does this need to be < 1??
    board_->SetTileNumber(i, (int)Wire.read());
  }

  Wire.beginTransmission(sending_board_addr_); // ask the sender
  Wire.write(byte(4)); // send all done
  Wire.endTransmission();

  // wait for its pin to turn off
  while ( -1 != PollSides()){
    Serial.println("Waiting for pin to shut down");
    delay(5);
  }
  Wire.end();

  // Set the other side pin high
  // Answer the questions the next node has
  // Turn my pin off when it is happy

  /*if (index_ > 19) {
   * send to next board.
   * }
   */


   //print out the board right now
   for (int i = 0; i < 19; i++) {
     Serial.print("Index: ");
     Serial.print(i);
     Serial.print("Tile Type: ");
     Serial.print(board_->GetTileType(i));
     Serial.print(" Tile Number:  ");
     Serial.print(board_->GetTileNumber(i));
     Serial.print("\n");
   }
}

int TileRunner::PollSides() {
  for (int i = 0; i < number_sides_; i++) {
    if (analogRead(input_side_pin_[i]) > 500){ // arbitrary Noise floor should be 1023
      return i;
    }
  }
  return -1; // None found
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

  Wire.begin(sending_board_addr_); // join i2c bus
  sending_data_ = true;
  Wire.onReceive(SendOnReceiveController);
  Wire.onRequest(SendOnRequestIndex);

  digitalWrite(output_side_pin_[side], HIGH);
  
  // sending_data will be set to false by a 
  // side effect of SendOndReceive Controller
  while (sending_data_) {
  }

  Wire.end();
  // set pin to low
  digitalWrite(output_side_pin_[side], LOW);
}


void TileRunner::SendOnReceiveController(int how_many){
  if( Wire.available()) {
      byte input = Wire.read(); // receive byte as a character
      if (input == byte(1)) { // Give back the index
        Wire.onRequest(SendOnRequestIndex);
        return;
        
      } else if (input == byte(2)) { // Give Back the types
        Wire.onRequest(SendOnRequestTileTypes);
        return;
        
      } else if (input == byte(3)) { // Give back the numbers
        Wire.onRequest(SendOnRequestTileNumbers);
        return;
        
      } else if (input == byte(4)) {
        Serial.println("All Done");
        sending_data_ = false;
        delay(100);
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
