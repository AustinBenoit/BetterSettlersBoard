#include <utility>
#include <array>
#include <stdio.h>

#include "boardGenerator.h"


Board::Board(std::array<std::pair<TileType, int>, 19> board) {
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

  // need to flip these around
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
