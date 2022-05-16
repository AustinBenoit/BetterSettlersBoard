#include <utility>
#include <array>
#include <stdio.h>

#include "boardGenerator.h"


Board::Board(std::array<std::pair<TileType, int>, 19> board) {
}

Board::Board() {
  board[0] = std::make_pair(TileType::wood, 1);
  board[1] = std::make_pair(TileType::wood, 1);
  board[2] = std::make_pair(TileType::wood, 1);
  board[3] = std::make_pair(TileType::wood, 1);
  board[4] = std::make_pair(TileType::wood, 1);
  board[5] = std::make_pair(TileType::wood, 1);
  board[6] = std::make_pair(TileType::wood, 1);
  board[7] = std::make_pair(TileType::wood, 1);
  board[8] = std::make_pair(TileType::wood, 1);
  board[9] = std::make_pair(TileType::wood, 1);
  board[10] = std::make_pair(TileType::wood, 1);
  board[11] = std::make_pair(TileType::wood, 1);
  board[12] = std::make_pair(TileType::wood, 1);
  board[13] = std::make_pair(TileType::wood, 1);
  board[14] = std::make_pair(TileType::wood, 1);
  board[15] = std::make_pair(TileType::wood, 1);
  board[16] = std::make_pair(TileType::wood, 1);
  board[17] = std::make_pair(TileType::wood, 1);
  board[18] = std::make_pair(TileType::wood, 1);
}

void Board::setTile(int tile, std::pair<TileType, int>tile_data) {
  board[tile]=tile_data;
}

std::pair<TileType, int> Board::getTile(int tile) { return board[tile]; }

void Board::printBoard(){
  const char* ascii_board =
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
/      \____/      \____/      \
\      /    \      /    \      /
 \____/      \____/      \____/
 /    \      /    \      /    \
/      \____/      \____/      \
\      /    \      /    \      /
 \____/      \____/      \____/
      \      /    \      /
       \____/      \____/
            \      /
             \____/)";

  // need to flip these around
  printf(ascii_board,
	 board[0].second, tileTypeEnumNames[board[0].first],
	 board[1].second, tileTypeEnumNames[board[1].first],
	 board[2].second, tileTypeEnumNames[board[2].first],
	 board[3].second, tileTypeEnumNames[board[3].first],
	 board[4].second, tileTypeEnumNames[board[4].first],
	 board[5].second, tileTypeEnumNames[board[5].first],
	 board[6].second, tileTypeEnumNames[board[6].first],
	 board[7].second, tileTypeEnumNames[board[7].first]
	 );
 }
