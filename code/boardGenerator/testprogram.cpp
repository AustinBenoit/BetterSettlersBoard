#include "boardGenerator.h"

int main () {
  Board b = GenerateBoard::generate();
  b.printBoard();
}
