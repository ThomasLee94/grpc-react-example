#include <unistd.h>  // Need usleep function (Unix systems only: Mac and Linux)
#include <iostream>

#include "board.h"

using namespace battleship;

static const int timestep = 1e6;  // Delay to use when sleeping: 1e6 = 1 second

int * AskUserForBoardSize() {
    // Ask user for Board size (number of rows and columns)
    int rows = 0, cols = 0;
    std::cout << "Choose board size (example: 6 rows, 8 columns)" << std::endl;
    std::cout << "Enter number of rows:    ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;
    if (rows <= 0 || cols <= 0) {
        // Set default Board size if either user-chosen size is invalid
        std::cout << "Chosen size is invalid: " << Board::CoordStr(rows, cols);
        rows = 6;
        cols = 8;
        std::cout << " -> Default: " << Board::CoordStr(rows, cols) << std::endl;
    }
    int *size = new int[2];
    size[0] = rows;
    size[1] = cols;
    return size;
}

void PlaceShipsFixed(Board& board) {
    // Place ships at fixed coordinates
    bool result;
    std::cout << "Placing ships at fixed coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before placing ships
    // This ship placement should succeed
    std::cout << "Placing ship from (1, 3) to (2, 3)";
    result = board.PlaceShipVertical(1, 2, 3);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (2, 1) to (4, 1)";
    result = board.PlaceShipVertical(2, 4, 1);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (1, 5) to (1, 7)";
    result = board.PlaceShipHorizontal(1, 5, 7);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should fail because its last cell is out of bounds
    std::cout << "Placing ship from (3, 2) to (6, 2)";
    result = board.PlaceShipVertical(3, 6, 2);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (4, 3) to (4, 6)";
    result = board.PlaceShipHorizontal(4, 3, 6);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should fail because it overlaps with another ship
    std::cout << "Placing ship from (2, 4) to (5, 4)";
    result = board.PlaceShipVertical(2, 5, 4);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (3, 7) to (5, 7)";
    result = board.PlaceShipVertical(3, 5, 7);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    std::cout << "Placed ships at fixed coordinates" << std::endl;
    usleep(timestep);  // Sleep after placing ship
}

void PlaceShipsUser(Board& board) {
    // Place ships at user-chosen coordinates
    const int kShips = 3;
    int row, col, size, count = 0;
    bool vertical, result;
    std::string v_or_h, orientation;
    for (int ship = 1; ship <= kShips; ++ship) {
        std::cout << "Place ship #" << ship << "..." << std::endl;
        std::cout << "Vertical or horizontal?  Enter v or h: ";
        std::cin >> v_or_h;
        // Vertical if first letter is "v" or horizontal if any other letter
        vertical = strncmp(v_or_h.c_str(), "v", 1) == 0;
        orientation = (vertical ? "vertically" : "horizontally");
        std::cout << "Enter size:   ";
        std::cin >> size;
        std::cout << "Enter row:    ";
        std::cin >> row;
        std::cout << "Enter column: ";
        std::cin >> col;
        std::cout << "Placing ship #" << ship << " " << orientation <<
            " at " << Board::CoordStr(row, col) << " with size " << size;
        if (vertical)
            result = board.PlaceShipVertical(row, row + size - 1, col);
        else
            result = board.PlaceShipHorizontal(row, col, col + size - 1);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
        board.Print();
        usleep(timestep);  // Sleep after placing ship
    }
    std::cout << "Placed " << kShips << " ships at chosen coordinates (" <<
        count << " succeeded, " << kShips - count << " failed)" << std::endl;
    usleep(timestep);  // Sleep after placing all ships
}

void FireMissilesFixed(Board& board) {
    // Fire missiles at fixed coordinates
    std::cout << "Firing missiles at fixed coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before firing missiles
    const int kMissiles = board.rows_ * board.cols_ / 4;
    int row = 1, col = 1, count = 0;
    bool result;
    for (int missile = 1; missile <= kMissiles; ++missile) {
        // Generate diagonal missile coordinates
        row = (row + 1) % board.rows_;
        col = (col + 2) % board.cols_;
        std::cout << "Firing missile #" << missile << " at " <<
            Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        // Print board after half and all missiles have been fired
        if (missile % (kMissiles / 2) == 0) {
            board.Print();
        }
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << kMissiles << " missiles at fixed coordinates (" <<
        count << " hit, " << kMissiles - count << " missed)" << std::endl;
    usleep(timestep);  // Sleep after firing all missiles
}

void FireMissilesUser(Board& board) {
    // Fire missiles at user-chosen coordinates
    const int kMissiles = 10;
    int row, col, count = 0;
    bool result;
    for (int missile = 1; missile <= kMissiles; ++missile) {
        std::cout << "Fire missile #" << missile << "..." << std::endl;
        std::cout << "Enter row:    ";
        std::cin >> row;
        std::cout << "Enter column: ";
        std::cin >> col;
        std::cout << "Firing missile at " << Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        board.Print();
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << kMissiles << " missiles at chosen coordinates (" <<
        count << " hit, " << kMissiles - count << " missed)" << std::endl;
}

int main(int argc, const char * argv[]) {
    int rows = 6, cols = 8;
    // Ask user for board size, then update rows and cols
    // int *size = AskUserForBoardSize();
    // rows = size[0];
    // cols = size[1];
    // delete [] size;
    // Create a new Board
    Board board = Board(rows, cols);
    board.Print();
    PlaceShipsFixed(board);
    // PlaceShipsUser(board);
    FireMissilesFixed(board);
    // FireMissilesUser(board);
}
