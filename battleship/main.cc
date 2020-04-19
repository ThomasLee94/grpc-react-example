#include <unistd.h>  // Need usleep function (Unix systems only: Mac and Linux)
#include <iostream>

#include "board.h"

using namespace battleship;

static const int timestep = 1e6;  // Delay to use when sleeping: 1e6 = 1 second

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


int main(int argc, const char * argv[]) {
    int rows = 6, cols = 8;
    // Create a new Board
    Board board = Board(rows, cols);
    board.Print();
    PlaceShipsFixed(board);
    FireMissilesFixed(board);
}
