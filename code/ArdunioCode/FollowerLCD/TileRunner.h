#ifndef TILERUNNER_H
#define TILERUNNER_H

#include "TileDisplay.h"
#include "Board.h"

class TileRunner {
private:
  // TODO This should be set and not a static const 
  int output_side_pin_[6] = {A0, A1, A2, A3, A6, A7};
  int input_side_pin_[6] = {3, 4, 5, 6, 9, 12};
  const int number_sides_ = 6;

  static int index_;
  Tile* tile_;
  static Board* board_;
  static bool sending_data_;

  static int GetNextOutputSide(int input_side);

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

public:
  TileRunner(Tile* tile, Board* board);
  void UpdateBoard(int side);
  void SendBoard(int side);
  int PollSides();
  void DisplayCurrentIndexTile();
  void SetIndex(int index);
};



#endif
