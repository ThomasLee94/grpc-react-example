#include "board.h"
#include "block.h"
#include "ship.h"

#include <string>
#include <vector>

namespace board {

Board::Board(const int y_coordinate, const int x_coordinate, const int rows, const int columns) {
    this->GRID = GRID[columns][rows];
}

} // namespace board
