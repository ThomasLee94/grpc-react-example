#include "board.h"
#include "block.h"
#include "ship.h"

#include <string>
#include <vector>

namespace board {

Board::Board(const int rows, const int columns) {
    this->GRID = GRID[columns][rows];
}

void Board::placeShip(const int y_start, const int y_end, const int x_start, const int x_end) {
    // vertical ship - x values remain the same
    if (std::abs(y_start - y_end) > 1) {
        for (int i = y_start; i < y_end, i++) {
            GRID[i][x_start] = 1
        }
    }
    
    // horizontal ship - y values remain the same
    if (std::abs(x_start - x_end) > 1) {
        for (int i = x_start; i < x_end, i++) {
            GRID[y_start][i] = i
        }
    }

}

} // namespace board
