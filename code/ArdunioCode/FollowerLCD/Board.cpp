#include "Board.h"  
#include "Arduino.h"

int Board::GetTileNumber(int tile_pos) {
  return numbers_[tile_pos];
  }
  
TileType Board::GetTileType(int tile_pos) {
  return tts_[tile_pos];
  }

uint16_t Board::GetTileColor(int tile_pos) {
  TileType tt = GetTileType(tile_pos);
  return TileTypeColor[tt];
}

void Board::SetTileType(int tile_pos, TileType tt){
  tts_[tile_pos] = tt;
}

void Board::SetTileNumber(int tile_pos, int number){
  numbers_[tile_pos] = number;
}

void Board::SetTile(int tile_pos, int number, TileType tt){
  SetTileNumber(tile_pos, number);
  SetTileType(tile_pos, tt);
}

void Board::RandomizeBoard(){
  randomize_numbers();
  randomize_tile_types();
}

void Board::swap_ints(volatile int* a, volatile int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

void Board::swap_tile_types(volatile TileType* a, volatile TileType* b) {
  TileType temp = *a;
  *a = *b;
  *b = temp;
}

void Board::randomize_numbers() {
  for (int k = 0; k < random(0, 100); k++) {
    for (int i = number_tiles_-1; i > 0; i--) {
        long j = random(0, number_tiles_);
        swap_ints(&numbers_[i], &numbers_[j]);
    }
  }
}

void Board::randomize_tile_types() {
  for (int k = 0; k < random(0, 100); k++) {
    for (int i = number_tiles_-1; i > 0; i--) {
        long j = random(0, number_tiles_);
        swap_tile_types(&tts_[i], &tts_[j]);
    }
  }
}
