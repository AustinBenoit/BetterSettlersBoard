#include "Board.h"  
  
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
