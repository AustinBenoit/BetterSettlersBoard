#include <array>
#include <utility>

#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H
enum TileType { wood, clay, sheep, iron, wheat, desert };

const char tileTypeEnumNames[6][3] = {
    [wood] = "WO", [clay] = "CL",  [sheep] = "SH",
    [iron] = "IR", [wheat] = "WH", [desert] = "DE"};

class Board {
private:
  // 19 Total tiles
  // Each slot holds the number and the tile type
  std::array< std::pair<TileType, int>,19> board;
  
public:
  Board(std::array<std::pair<TileType, int>,19> board);
  Board();
  void setTile(int tile, std::pair<TileType, int> tile_data);
  std::pair<TileType, int> getTile(int tile);
  void printBoard();
};



class GenerateBoard {
public:
  static Board generate ();
private:
  GenerateBoard() {};
};



#endif //BOARDGENERATOR_H
