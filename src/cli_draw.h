//
// Created by Guthorak on 10/26/18.
//

#ifndef PIE_CLI_DRAW_H
#define PIE_CLI_DRAW_H

#include <array>
#include <iostream>

#include "src/board.h"

namespace pie {

class CliDrawer {
 public:
  CliDrawer(Board& board);
  void DrawBoard() const;
  //overload << voor board voor in DrawBoard();


 private:
  Board& board_;
};



} //namespace pie
#endif //PIE_CLI_DRAW_H
