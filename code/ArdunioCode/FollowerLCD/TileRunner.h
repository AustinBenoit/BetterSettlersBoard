#ifndef TILERUNNER_H
#define TILERUNNER_H

#include "TileDisplay.h"
#include "Board.h"

class TileRunner {
private:
  const static int sending_board_addr_ = 50;
  const static int getting_board_addr_ = 51;
  // TODO This should be set and not a static const 
  int* output_side_pin_;
  int* input_side_pin_;
  const int number_sides_ = 6;

  static int index_;
  Tile* tile_;
  static Board* board_;
  
  volatile static bool sending_data_;

  /*
   * 1 : send back index
   * 2 : send back types
   * 3 : send back numbers
   * 4 : finish transmission
   */
  static void SendOnReceiveController(int how_many);

  static void SendOnRequestIndex();
  static void SendOnRequestTileTypes();
  static void SendOnRequestTileNumbers();
  static void ResetBoard();

public:
  volatile static bool send_new_board_;
  TileRunner(Tile* tile, Board* board, int* output_sides, int* input_sides);

  int GetNextOutputSide(int input_side);
  void UpdateBoard();
  void SendBoard(int side);
  int PollSides();
  void DisplayCurrentIndexTile();
  void SetIndex(int index);
  int GetIndex();
  void SerialPrintBoard();
  void ConfigureRestBoard(int reset_pin);
};
#endif
