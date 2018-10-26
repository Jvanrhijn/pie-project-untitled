//
// Created by Guthorak on 10/26/18.
//

#include "src/cli_draw.h"

namespace pie {

CliDrawer::CliDrawer(pie::Board &board)
: board_(board)
{}

void CliDrawer::DrawBoard() const {
  for (int row_count=0; row_count<board_.side(); row_count++) {
    for (int col_count=0; col_count<board_.side(); col_count++) {

    }
  }
}

} //namespace pie