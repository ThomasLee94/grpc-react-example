#include "board.h"
#include "block.h"
#include "ship.h"

#include <string>
#include <vector>

namespace board {

Board::Board(const int rows, const int columns) {
    grid_ = grid_[columns][rows];
}

void Board::placeShip(
        const int y_start,
        const int y_end,
        const int x_start,
        const int x_end) {
    // ensuring given coordinates are within the bounds of the grid
    if (y_start >= rows || y_end > rows || x_start >= columns || x_end > columns) {
        throw "Ship is either placed out of bounds or collides with another ship";
    }

    // ensuring ship placements doesnt collide with a ship that has been placed

    // vertical ship - x values remain the same
    if (std::abs(y_start - y_end) > 1) {
        for (int i = y_start; i < y_end, i++) {
            grid_[i][x_start] = 1
        }
    }
    
    // horizontal ship - y values remain the same
    if (std::abs(x_start - x_end) > 1) {
        for (int i = x_start; i < x_end, i++) {
            grid_[y_start][i] = i
        }
    }

}

} // namespace board
