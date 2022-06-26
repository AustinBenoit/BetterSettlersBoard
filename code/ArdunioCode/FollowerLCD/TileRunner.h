#ifndef TILERUNNER_H
#define TILERUNNER_H

#include "TileDisplay.h"
#include "Board.h"

class TileRunner {
private:
  // TODO This should be set and not a static const 
  int output_side_pin_[6] = {A0, A1, A2, A3, A6, A7};
  int input_side_pin_[6] = {3, 4, 5, 6, 7, 12};
  static const int number_sides_ = 6;

  int index_;
  Tile* tile_;
  Board* board_;

  int GetOutputSide(int input_side);

public:
  TileRunner(Tile* tile, Board* board);
  void UpdateBoard(int input_pin);
  void KickOff();
  int PollSides();
  void DisplayCurrentIndexTile();
  void SetIndex(int index);
};

#endif
