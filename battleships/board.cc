#include "board.h"
#include "block.h"
#include "ship.h"

#include <string>
#include <vector>

namespace board {

Board::Board(const int rows, const int columns) {
    grid_ = grid_[columns][rows*2];
}

void Board::placeShipVert(
        const int y_start, const int y_end,
        const int x_start,
        const int player) {
    // ensuring given coordinates are within the bounds of the grid
    if (y_start >= rows || y_end > rows || x_start >= columns) {
        throw "Ship is either placed out of bounds";
    }

    // vertical ship - x values remain the same
    if (std::abs(y_start - y_end) > 1) {
        for (int i = y_start; i < y_end, i++) {
            if (player == 1) {
                if (grid_[i][x_start] == 1) {
                    throw "Ship collides with another ship";
                }
                grid_[i][x_start] = 1
            }

            if (grid_[i+rows][x_start] == 1) {
                    throw "Ship collides with another ship";
                }
            grid_[i+rows][x_start] = 1
            
        }
    }
    
    

}

void Board::placeShipHorizontal(
        const int y_start,
        const int x_start,const int x_end,
        const int player) {

    // ensuring given coordinates are within the bounds of the grid
    if (y_start >= rows || x_start >= columns || x_end > columns) {
        throw "Ship is either placed out of bounds";
    }

    // horizontal ship - y values remain the same
    if (std::abs(x_start - x_end) > 1) {
        for (int i = x_start; i < x_end, i++) {
            if (player == 1) {
                if (grid_[y_start][i] == 1) {
                    throw "Ship collides with another ship";
                }
                grid_[y_start][i] = 1
            } 

            if (grid_[y_start+rows][i] == 1) {
                    throw "Ship collides with another ship";
                }
            grid_[y_start+rows][i] = 1
        }
    }
}

bool Board::fireMissile(const int y, const int x) {
    // other players grid?
    if (grid_[y_coordinate][x_start]) == 1 {
        return true
    }

    return false
}

} // namespace board
