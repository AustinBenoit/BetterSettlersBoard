#ifndef BOARD_H
#define BOARD_H

#include "Color.h"
#include <stdint.h>

enum TileType { wood = 0, clay = 1, sheep = 2, iron = 3, wheat = 4, desert = 5 };

const uint16_t TileTypeColor[] {
    [wood] = DARKGREEN, [clay] = BRRED,  [sheep] = GREEN,
    [iron] = GRAYBLUE, [wheat] = YELLOW, [desert] = BROWN };
/* The boards positons are laid out in the following order:
 *  The number in the tile is its "Position"
 *               ____
 *              /    \
 *         ____/  18  \____
 *        /    \      /    \
 *   ____/  12  \____/  17  \____
 *  /    \      /    \      /    \
 * / 11   \____/  13  \____/  16  \
 * \      /    \      /    \      /
 *  \____/  10  \____/  14  \____/
 *  /    \      /    \      /    \
 * /  03  \____/  09  \____/  15  \
 * \      /    \      /    \      /
 *  \____/  04  \____/  08  \____/
 *  /    \      /    \      /    \
 * /  02  \____/  05  \____/  07  \
 * \      /    \      /    \      /
 *  \____/  01  \____/  06  \____/
 *       \      /    \      /
 *        \____/  00  \____/
 *             \      /
 *              \____/
 * 
 */
 
class Board {
private:
  // 19 Total tiles
  // Each slot holds the number and the tile type

  // The inital Starting board represent the games suggested starting board
  int numbers_[19] = {
    5,
    8,
    9,
    12,
    11,
    3,
    6,
    11,
    4,
    00,//desert
    6,
    10,
    2,
    4,
    3,
    5,
    8,
    10,
    9
  };
  
  TileType tts_[19] = {
    TileType::clay,
    TileType::wood,
    TileType::wheat,
    TileType::wheat,
    TileType::wood,
    TileType::iron,
    TileType::wheat,
    TileType::sheep,
    TileType::wheat,
    TileType::desert,
    TileType::clay,
    TileType::iron,
    TileType::sheep,
    TileType::sheep,
    TileType::wood,
    TileType::sheep,
    TileType::iron,
    TileType::clay,
    TileType::wood
  };
  
public:
  void SetTile(int tile_pos, int number, TileType tt);
  void SetTileType(int tile_pos, TileType tt);
  void SetTileNumber(int tile_pos, int number);
  void RandomizeBoard();
  int GetTileNumber(int tile);
  TileType GetTileType(int tile_pos);
  uint16_t GetTileColor(int tile_pos);
};

#endif // BOARDSETUP_H
