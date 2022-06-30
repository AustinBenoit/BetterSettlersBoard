#include "TileRunner.h"
#include "Color.h"
#include "Wire.h"

int TileRunner::index_;
volatile bool TileRunner::sending_data_; 
Board* TileRunner::board_;
volatile bool TileRunner::send_new_board_;

int TileRunner::GetNextOutputSide(int input_side){
  switch (index_) {
    case 2:
    case 12:
      return (input_side  - 2) % number_sides_;
    case 3:
    case 11:
      return (input_side  - 1) % number_sides_;
    case 6:
    case 16:
      return (input_side  + 2) % number_sides_;
    case 7:
    case 15:
      return (input_side  + 1) % number_sides_;
    default:
      return (input_side  + 3) % number_sides_;
  }
}

TileRunner::TileRunner(Tile* tile, Board* board, int* output_sides, int* input_sides) {
  board_ = board;
  TileRunner::tile_ = tile;
  TileRunner::index_ = 0;

  output_side_pin_ = output_sides;
  input_side_pin_ = input_sides;

   sending_data_ = false;
   
   send_new_board_ = false;

  for (int i = 0; i < number_sides_; i++) {
     pinMode(TileRunner::output_side_pin_[i], OUTPUT);
     pinMode(TileRunner::input_side_pin_[i], INPUT);
  }

  TileRunner::tile_->DisplayTileNoNumber(LIGHTBLUE);
}

void TileRunner::UpdateBoard(){
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

  // wait for its pin to turn off
  while ( -1 != PollSides()){
    Wire.beginTransmission(sending_board_addr_); // ask the sender
    Wire.write(byte(4)); // send all done
    Wire.endTransmission();
    Serial.println("Waiting for pin to shut down");
    delay(100);
  }
  
  Wire.end();
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
  Serial.println("Sending Board");

  Wire.begin(sending_board_addr_); // join i2c bus
  sending_data_ = true;
  Wire.onReceive(SendOnReceiveController);
  Wire.onRequest(SendOnRequestIndex);

  digitalWrite(output_side_pin_[side], HIGH);

  // sending_data will be set to false by a 
  // side effect of SendOndReceive Controller
  while (sending_data_ != false) {
    delay(100); 
    Serial.println("waiting to finish");
  }

  Wire.end();
  // set pin to low
  digitalWrite(output_side_pin_[side], LOW);
}

void TileRunner::SendOnReceiveController(int how_many){
  if( Wire.available()) {
      byte input = Wire.read(); // receive byte as a character
      if (input == byte(1)) { // Give back the index
        Serial.println("Index");
        Wire.onRequest(SendOnRequestIndex);
        return;
        
      } else if (input == byte(2)) { // Give Back the types
        Serial.println("Types");
        Wire.onRequest(SendOnRequestTileTypes);
        return;
        
      } else if (input == byte(3)) { // Give back the numbers
        Serial.println("Numbers");
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

void TileRunner::SerialPrintBoard() {
   for (int i = 0; i < board_->number_tiles_; i++) {
    Serial.print("Index: ");
    Serial.print(i);
    Serial.print(" Tile Type: ");
    Serial.print(board_->GetTileType(i));
    Serial.print(" Tile Number: ");
    Serial.print(board_->GetTileNumber(i));
    Serial.println();
  }
}

void TileRunner::ResetBoard(){

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 1000) {
    board_->RandomizeBoard();
    send_new_board_ = true;

    for (int i = 0; i < board_->number_tiles_; i++) {
      Serial.print("Index: ");
      Serial.print(i);
      Serial.print(" Tile Type: ");
      Serial.print(board_->GetTileType(i));
      Serial.print(" Tile Number: ");
      Serial.print(board_->GetTileNumber(i));
      Serial.println();
    }
  }
  last_interrupt_time = interrupt_time;
}

void TileRunner::ConfigureRestBoard(int reset_pin){
  pinMode(reset_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(reset_pin), ResetBoard, RISING);
}

int TileRunner::GetIndex() {
  return index_;
}
