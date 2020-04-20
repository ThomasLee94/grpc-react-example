#include "board.h"

#include <iostream>

namespace battleship {

Board::Board(const int rows, const int cols)
        : rows_(rows), cols_(cols) {
    // grid_ = new int[rows_][cols_]();
    // This should initialize a contiguous 2D array but throws a compiler error:
    // "only the first dimension of an allocated array may have dynamic size"

    // Instead we need to initialize an array of pointers to scattered row arrays
    // Code to create 2D array adapted from https://stackoverflow.com/a/936702
    grid_ = new int*[rows_]();
    for (int row = 0; row < rows_; ++row) {
        // Initialize each row to an array of ints
        grid_[row] = new int[cols_]();
        // Need () to initialize grid cells to zero or values will be uninitialized
        // Code to initialize row adapted from https://stackoverflow.com/a/16239446
        // Without () above, we need to loop over columns to initialize each cell
        // for (int col = 0; col < cols_; ++col) {
        //     // Initialize each cell to zero
        //     grid_[row][col] = 0;
        // }
    }

    // It is possible to dynamically allocate a contiguous 2D block of memory
    // where rows and columns vary at runtime and preserve 2-subscript access.
    // Example code found in this answer: https://stackoverflow.com/a/29375830

    // Alternative pseudo-2D array solution: https://stackoverflow.com/a/28841507
}

Board::~Board() {
    // Code to delete 2D array adapted from https://stackoverflow.com/a/936709
    for (int row = 0; row < rows_; ++row) {
        // Delete each row array
        delete [] grid_[row];
    }
    // Delete array of pointers to row arrays
    delete [] grid_;
}

bool Board::PlaceShipVertical(const int row_start, const int row_end, const int col) {
    // Ensure given coordinates are valid and within the bounds of the grid
    if (row_end - row_start < 0 ||
        !IsInBounds(row_start, col) ||
        !IsInBounds(row_end, col)) {
        // throw "Ship coordinates are out of bounds: " << CoordStr(row, col);
        return false;  // Invalid coordinates
    }
    // Ship is vertical, so loop over rows, column remains the same
    for (int row = row_start; row <= row_end; ++row) {
        // Ensure each coordinate does not overlap with another ship
        if (grid_[row][col] > 0) {
            // throw "Ship overlaps with another ship at " << CoordStr(row, col);
            return false;  // Ship overlaps
        }
    }
    // Place ship after ensuring coordinates do not overlap with another ship
    for (int row = row_start; row <= row_end; ++row) {
        grid_[row][col] = 1;
    }
    return true;  // Success
}

bool Board::PlaceShipHorizontal(const int row, const int col_start, const int col_end) {
    // Ensure given coordinates are valid and within the bounds of the grid
    if (col_end - col_start < 0 ||
        !IsInBounds(row, col_start) ||
        !IsInBounds(row, col_end)) {
        // throw "Ship coordinates are out of bounds: " << CoordStr(row, col);
        return false;  // Invalid coordinates
    }
    // Ship is horizontal, so loop over columns, row remains the same
    for (int col = col_start; col <= col_end; ++col) {
        // Ensure each coordinate does not overlap with another ship
        if (grid_[row][col] > 0) {
            // throw "Ship overlaps with another ship at " << CoordStr(row, col);
            return false;  // Ship overlaps
        }
    }
    // Place ship after ensuring coordinates do not overlap with another ship
    for (int col = col_start; col <= col_end; ++col) {
        grid_[row][col] = 1;
    }
    return true;  // Success
}

bool Board::FireMissile(const int row, const int col) {
    if (!IsInBounds(row, col)) {
        // throw "Missile coordinates are out of bounds: " << CoordStr(row, col);
        return false;  // Invalid coordinates
    }
    if (grid_[row][col] > 0) {
        grid_[row][col] = -1;
        return true;  // Hit
    }
    grid_[row][col] = -1;
    return false;  // Miss
}

bool Board::IsInBounds(const int row, const int col) const {
    // Ensure given coordinates are each valid indexes (within bounds of grid)
    return (0 <= row && row < rows_ &&
            0 <= col && col < cols_);
}

bool Board::IsFull() const {
    // Loop over each row and column to check if all grid cells are full
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            if (grid_[row][col] == 0)
                return false;  // Found empty cell
        }
    }
    return true;  // All cells are full
}

const int Board::Rows() const {
    return rows_;
}

const int Board::Cols() const {
    return cols_;
}

const int * Board::Size() const {
    // Array to store board size: (rows, cols)
    int *size = new int[2]();
    size[0] = rows_;
    size[1] = cols_;
    return size;
}

const std::string Board::CoordStr(const int row, const int col) {
    // Format given coordinates as string: (row, col)
    return "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
    // Using std::to_string is recommended: https://stackoverflow.com/a/900035
    // Alternative is using string stream but this requires #include <sstream>
    // std::stringstream sstm;
    // sstm << "(" << row << ", " << col << ")";
    // return sstm.str();
}

const std::string Board::CellStr(const int row, const int col) const {
    const int cell = grid_[row][col];  // Get cell value to show conditionally
    return (cell == 0 ? " " :  // Show empty cells as " " blank for visibility
           (cell > 0 ? "S" : "*"));  // Show ships as "S" and missiles as "*"
}

void Board::Print() const {
    // Box drawing characters: ─━  │┃  ┼╋┿╂  ├┠┣  ┤┨┫  ┬┯┳  ┴┷┻  ┌┏  ┐┓  └┗  ┘┛
    // Reference: https://en.wikipedia.org/wiki/Box-drawing_character#Encodings
    std::string header1 = " column";
    std::string header2 = "   ";
    std::string top     = "row┏";
    std::string divider = "   ┣";
    std::string bottom  = "   ┗";
    // Generate header and horizontal dividers based on number of columns
    for (int col = 0; col < cols_; ++col) {
        header1  = "  " + header1 + "  ";  // Center the word "column"
        header2 += "  " + std::to_string(col) + (col < 10 ? " " : "");  // Right-pad column number
        top     += "━━━" + std::string(col < cols_-1 ? "┳" : "┓");  // Last column is different
        divider += "━━━" + std::string(col < cols_-1 ? "╋" : "┫");  // Last column is different
        bottom  += "━━━" + std::string(col < cols_-1 ? "┻" : "┛");  // Last column is different
    }
    std::cout << header1 << std::endl;
    std::cout << header2 << std::endl;
    std::cout << top << std::endl;
    // Loop over each row to generate string to display its cells
    for (int row = 0; row < rows_; ++row) {
        std::string row_str = (row < 10 ? " " : "") + std::to_string(row) + " ┃";  // Left-pad row number
        // Loop over each column to generate row string one cell at a time
        for (int col = 0; col < cols_; ++col) {
            row_str += " " + CellStr(row, col) + " ┃";
        }
        std::cout << row_str << std::endl;
        std::cout << (row < rows_-1 ? divider : bottom) << std::endl;  // Last row is different
    }
}

}  // namespace battleship
