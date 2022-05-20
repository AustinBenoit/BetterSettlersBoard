#include <utility>
#include <array>
#include <stdio.h>
#include <vector>
#include <random>

#include "boardGenerator.h"


Board::Board(std::array<std::pair<TileType, int>, 19> new_board) {
  board[0] = new_board[0];
  board[1] = new_board[1];
  board[2] = new_board[2];
  board[3] = new_board[3];
  board[4] = new_board[4];
  board[5] = new_board[5];
  board[6] = new_board[6];
  board[7] = new_board[7];
  board[8] = new_board[8];
  board[9] = new_board[9];
  board[10] = new_board[10];
  board[11] = new_board[11];
  board[12] = new_board[12];
  board[13] = new_board[13];
  board[14] = new_board[14];
  board[15] = new_board[15];
  board[16] = new_board[16];
  board[17] = new_board[17];
  board[18] = new_board[18];
  }

Board::Board() {
  board[0] = std::make_pair(TileType::wheat, 9);
  board[1] = std::make_pair(TileType::wood, 8);
  board[2] = std::make_pair(TileType::wheat, 12);
  board[3] = std::make_pair(TileType::clay, 5);
  board[4] = std::make_pair(TileType::wood, 11);
  board[5] = std::make_pair(TileType::iron, 10);
  board[6] = std::make_pair(TileType::iron, 3);
  board[7] = std::make_pair(TileType::clay, 6);
  board[8] = std::make_pair(TileType::wheat, 6);
  board[9] = std::make_pair(TileType::desert, 00);
  board[10] = std::make_pair(TileType::sheep, 2);
  board[11] = std::make_pair(TileType::wheat, 4);
  board[12] = std::make_pair(TileType::sheep, 4);
  board[13] = std::make_pair(TileType::sheep, 11);
  board[14] = std::make_pair(TileType::wood, 3);
  board[15] = std::make_pair(TileType::wood, 9);
  board[16] = std::make_pair(TileType::sheep, 5);
  board[17] = std::make_pair(TileType::clay, 10);
  board[18] = std::make_pair(TileType::iron, 8);
}

void Board::setTile(int tile, std::pair<TileType, int>tile_data) {
  board[tile]=tile_data;
}

std::pair<TileType, int> Board::getTile(int tile) { return board[tile]; }

void Board::printBoard(){
  const char *ascii_board =
R"(              ____
             /    \
        ____/%2d  %s\____
       /    \      /    \
  ____/%2d  %s\____/%2d  %s\____
 /    \      /    \      /    \
/%2d  %s\____/%2d  %s\____/%2d  %s\
\      /    \      /    \      /
 \____/%2d  %s\____/%2d  %s\____/
 /    \      /    \      /    \
/%2d  %s\____/%2d  %s\____/%2d  %s\
\      /    \      /    \      /
 \____/%2d  %s\____/%2d  %s\____/
 /    \      /    \      /    \
/%2d  %s\____/%2d  %s\____/%2d  %s\
\      /    \      /    \      /
 \____/%2d  %s\____/%2d  %s\____/
      \      /    \      /
       \____/%2d  %s\____/
            \      /
             \____/
)";


  printf(ascii_board,
	 board[0].second, tileTypeEnumNames[board[0].first],
	 board[1].second, tileTypeEnumNames[board[1].first],
	 board[2].second, tileTypeEnumNames[board[2].first],
	 board[3].second, tileTypeEnumNames[board[3].first],
	 board[4].second, tileTypeEnumNames[board[4].first],
	 board[5].second, tileTypeEnumNames[board[5].first],
	 board[6].second, tileTypeEnumNames[board[6].first],
	 board[7].second, tileTypeEnumNames[board[7].first],
	 board[8].second, tileTypeEnumNames[board[8].first],
	 board[9].second, tileTypeEnumNames[board[9].first],
	 board[10].second, tileTypeEnumNames[board[10].first],
	 board[11].second, tileTypeEnumNames[board[11].first],
	 board[12].second, tileTypeEnumNames[board[12].first],
	 board[13].second, tileTypeEnumNames[board[13].first],
	 board[14].second, tileTypeEnumNames[board[14].first],
	 board[15].second, tileTypeEnumNames[board[15].first],
	 board[16].second, tileTypeEnumNames[board[16].first],
	 board[17].second, tileTypeEnumNames[board[17].first],
	 board[18].second, tileTypeEnumNames[board[18].first]
	 );
 }

Board GenerateBoard::generate() {

  std::vector<TileType> tile_array {
    wood, wood, wood, wood,
    clay, clay, clay,
    sheep, sheep, sheep, sheep,
    iron, iron, iron,
    wheat, wheat, wheat, wheat,
    desert };

  std::vector<int> num_array {
    2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
  };

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(tile_array.begin(), tile_array.end(), g);
  std::shuffle(num_array.begin(), num_array.end(), g);

  Board b;
  int offset = 0; // off set the number array after seeing the desert
  for (int i = 0; i < 19; i++) {
    int num = num_array[i - offset];
    if (tile_array[i] == TileType::desert){
      num = 0;
      offset = 1;
    }
    
    b.setTile(i, std::make_pair(tile_array[i], num));
  }

  return b;
}
