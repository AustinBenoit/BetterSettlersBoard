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
