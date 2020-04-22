#include "player.h"

#include <string.h>
#include <iostream>
#include "random.h"

namespace battleship {

Player::Player(const int id, const std::string name)
        : id_(id), name_(name) {
}

const int Player::ID() const {
    return id_;
}

const std::string Player::Name() const {
    // return name_;
    return "Player " + std::to_string(id_) + ": " + name_;
}

const int * Player::GetBoardSize() const {
    static const int kMinBoardSize[] = {2, 3};  // Min board size: (rows, cols)
    int *size = new int[2]();  // Store user-chosen board size: (rows, cols)
    // Ask user for each dimension of board size: first rows, then cols
    std::cout << "Choose board size (example: 6 rows, 8 columns)" << std::endl;
    int dimension = 0;  // Dimension of board size: 0 = rows, 1 = cols
    while (dimension < 2) {
        const std::string rows_or_cols = (dimension == 0 ? "rows" : "columns");
        std::cout << "Enter number of " << rows_or_cols << ":   ";
        std::cin >> size[dimension];
        // Check if user-chosen size is valid
        if (size[dimension] >= kMinBoardSize[dimension])
            ++dimension;  // Valid, so get next dimension (rows -> cols -> done)
        else
            std::cout << "Invalid number of " << rows_or_cols << ": " <<
                                                 size[dimension] << std::endl;
    }
    // Once validated, show user their chosen board size
    std::cout << "Chosen board size: " << size[0] << " rows, " <<
                                          size[1] << " columns" << std::endl;
    return size;
}

const int * Player::GetShipCoords(const Board& board) const {
    const int *board_size = board.Size();  // Board size: (rows, cols)
    int *coords = new int[4]();  // Ship coordinates: (row, col, size, vertical)

    // Ask user for ship orientation: vertical or horizontal
    std::cout << "Choose ship orientation: vertical or horizontal" << std::endl;
    std::string v_or_h, orientation;  // Strings for user input and output
    bool vertical, horizontal;  // Ship orientation: vertical xor horizontal
    while (true) {
        std::cout << "Enter 'v' or 'h': ";
        std::cin >> v_or_h;
        // Check first letter or response: vertical if "v" or horizontal if "h"
        vertical   = strncmp(v_or_h.c_str(), "v", 1) == 0;
        horizontal = strncmp(v_or_h.c_str(), "h", 1) == 0;
        // Check if user-chosen ship orientation is valid
        if (vertical || horizontal)
            break;  // Valid, so advance to choosing ship size
        else
            std::cout << "Invalid input:    " << v_or_h << std::endl;
    }
    // Once validated, show user their chosen ship orientation
    orientation = (vertical ? "vertical" : "horizontal");
    std::cout << "Chosen ship orientation: " << orientation << std::endl;
    coords[3] = static_cast<int>(vertical);

    // Calculate min and max ship size considering ship orientation (dimension)
    const int ship_dimension = static_cast<int>(horizontal);  // false/true -> 0/1 (rows/cols)
    const int min_ship_size = std::min(board_size[ship_dimension], 2);
    const int max_ship_size = std::min(board_size[ship_dimension], 5);
    // Ask user for ship size
    std::cout << "Choose ship size (min: " << min_ship_size <<
                                 ", max: " << max_ship_size << ")" << std::endl;
    int size = 0;
    while (true) {
        std::cout << "Enter size:   ";
        std::cin >> size;
        // Check if user-chosen ship size is valid (in range on its dimension)
        if (min_ship_size <= size && size <= max_ship_size)
            break;  // Valid, so advance to choosing ship coordinates
        else
            std::cout << "Invalid size: " << size << std::endl;
    }
    // Once validated, show user their chosen ship size
    std::cout << "Chosen ship size: " << size << std::endl;
    coords[2] = size;

    // Ask user for each dimension of ship coordinates: first row, then col
    std::cout << "Choose ship coordinates: (row, column)" << std::endl;
    int dimension = 0;  // Dimension of ship coordinates: 0 = row, 1 = col
    while (dimension < 2) {
        const std::string row_or_col = (dimension == 0 ? "row" : "column");
        std::cout << "Enter " << row_or_col << ":   ";
        std::cin >> coords[dimension];
        // Check if user-chosen ship coordinate is valid considering ship size
        const int ship_size_this_dim = (dimension == horizontal ? size : 1);
        const int max_ship_coord = board_size[dimension] - ship_size_this_dim;
        if (0 <= coords[dimension] && coords[dimension] <= max_ship_coord)
            ++dimension;  // Valid, so get next dimension (row -> col -> done)
        else
            std::cout << "Invalid " << row_or_col << ": " <<
                                       coords[dimension] << std::endl;
    }
    // Once validated, show user their chosen ship coordinates
    std::cout << "Chosen ship coordinates: " << Board::CoordStr(coords[0], coords[1]) << std::endl;
    std::cout << "Chosen ship placement summary: " << orientation <<
        " ship with size " << size << " at " << Board::CoordStr(coords[0], coords[1]) << std::endl;
    return coords;
}

const int * Player::GetMissileCoords(const Board& board) const {
    const int *board_size = board.Size();  // Board size: (rows, cols)
    int *coords = new int[2]();  // Missile coordinates: (row, col)

    // Ask user for each dimension of missile coordinates: first row, then col
    std::cout << "Choose missile coordinates: (row, column)" << std::endl;
    int dimension = 0;  // Dimension of missile coordinates: 0 = row, 1 = col
    while (dimension < 2) {
        const std::string row_or_col = (dimension == 0 ? "row" : "column");
        std::cout << "Enter " << row_or_col << ":   ";
        std::cin >> coords[dimension];
        // Check if user-chosen missile coordinate is valid
        if (0 <= coords[dimension] && coords[dimension] < board_size[dimension])
            ++dimension;  // Valid, so get next dimension (row -> col -> done)
        else
            std::cout << "Invalid " << row_or_col << ": " <<
                                       coords[dimension] << std::endl;
    }
    // Once validated, show user their chosen missile coordinates
    std::cout << "Chosen missile coordinates: " << Board::CoordStr(coords[0], coords[1]) << std::endl;
    return coords;
}

RandomPlayer::RandomPlayer(const int id, const std::string name)
        : Player(id, name), id_(id), name_(name) {
}

const int * RandomPlayer::GetBoardSize() const {
    int *size = new int[2]();  // Store board size: (rows, cols)
    int rows, cols;
    RandomGenerator random;
    // Generate random integer for each dimension of board size
    size[0] = rows = random.RandomInt(2, 8);
    size[1] = cols = random.RandomInt(3, 10);
    // Print randomly generated board size
    // std::cout << "Random board size: " << rows << " rows, " <<
    //                                       cols << " columns" << std::endl;
    return size;
}

const int * RandomPlayer::GetShipCoords(const Board& board) const {
    const int *board_size = board.Size();  // Board size: (rows, cols)
    int *coords = new int[4]();  // Ship coordinates: (row, col, size, vertical)
    int row, col, size, vertical;
    RandomGenerator random;
    // Generate random integer for ship orientation
    coords[3] = vertical = random.RandomInt(0, 1);  // 0 = horizontal, 1 = vertical
    // Calculate min and max ship size considering ship orientation (dimension)
    const int ship_dimension = !vertical;  // true/false -> 0/1 (rows/cols)
    const int min_ship_size = std::min(board_size[ship_dimension], 2);
    const int max_ship_size = std::min(board_size[ship_dimension], 5);
    // Generate random integer for ship size within range on its dimension
    coords[2] = size = random.RandomInt(min_ship_size, max_ship_size);
    // Generate random integer for each dimension of ship coordinates
    // considering ship orientation and size along each dimension
    coords[0] = row = random.RandomInt(0, board.Rows() - (vertical ? size : 1));
    coords[1] = col = random.RandomInt(0, board.Cols() - (vertical ? 1 : size));
    // Print randomly generated ship orientation, size, and coordinates
    // const std::string orientation = (vertical ? "vertical" : "horizontal");
    // std::cout << "Random ship placement: " << orientation << " ship with size " <<
    //     size << " at " << Board::CoordStr(row, col) << std::endl;
    return coords;
}

const int * RandomPlayer::GetMissileCoords(const Board& board) const {
    int *coords = new int[2]();  // Store missile coordinates: (row, col)
    int row, col;
    RandomGenerator random;
    // Generate random integer for each dimension of missile coordinates
    coords[0] = row = random.RandomInt(0, board.Rows() - 1);
    coords[1] = col = random.RandomInt(0, board.Cols() - 1);
    // Print randomly generated missile coordinates
    // std::cout << "Random missile coordinates: " << Board::CoordStr(row, col) << std::endl;
    return coords;
}

} // namepace battleship
