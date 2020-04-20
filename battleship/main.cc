#include <unistd.h>  // Need usleep function (Unix systems only: Mac and Linux)
#include <string.h>
#include <iostream>

#include "battleship/random.h"
#include "battleship/board.h"
#include "battleship/player.h"
#include "battleship/game.h"


using ::battleship;

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
        std::cout << " -> Default: "
            << Board::CoordStr(rows, cols) << std::endl;
    }
    int *size = new int[2];
    size[0] = rows;
    size[1] = cols;
    return size;
}

void PlaceShipsFixed(const Board& board) {
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

void PlaceShipsRandom(Board& board, const int num_ships = 5) {
    // Place ships at random coordinates
    std::cout << "Placing " << num_ships << " ships at random coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before placing ships
    RandomGenerator random;
    int row, col, size, vertical, result, count = 0;
    std::string orientation;
    for (int ship = 1; ship <= num_ships; ++ship) {
        // Generate random integer for ship orientation
        vertical = random.RandomInt(0, 1);  // 0 = horizontal, 1 = vertical
        // Generate random integer for ship size within range on its dimension
        size = random.RandomInt(1, (vertical ? board.Rows() : board.Cols()));
        // Generate random integer for each dimension of ship coordinates
        // considering ship orientation and size along each dimension
        row = random.RandomInt(0, board.Rows() - (vertical ? size : 1));
        col = random.RandomInt(0, board.Cols() - (vertical ? 1 : size));
        orientation = (vertical ? "vertically" : "horizontally");
        std::cout << "Placing ship #" << ship << " " << orientation <<
            " at " << Board::CoordStr(row, col) << " with size " << size;
        if (vertical)
            result = board.PlaceShipVertical(row, row + size - 1, col);
        else
            result = board.PlaceShipHorizontal(row, col, col + size - 1);
        count += result;
        std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
        board.Print();
        usleep(timestep);  // Sleep after placing ship
    }
    std::cout << "Placed " << num_ships << " ships at random coordinates (" <<
        count << " succeeded, " << num_ships - count << " failed)" << std::endl;
    usleep(timestep);  // Sleep after placing all ships
}

void PlaceShipsUser(Board& board, const int num_ships = 3) {
    // Place ships at user-chosen coordinates
    std::cout << "Placing " << num_ships << " ships at user-chosen coordinates..." << std::endl;
    int row, col, size, vertical, result, count = 0;
    std::string v_or_h, orientation;
    for (int ship = 1; ship <= num_ships; ++ship) {
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
        count += result;
        std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
        board.Print();
        usleep(timestep);  // Sleep after placing ship
    }
    std::cout << "Placed " << num_ships << " ships at user-chosen coordinates (" <<
        count << " succeeded, " << num_ships - count << " failed)" << std::endl;
    usleep(timestep);  // Sleep after placing all ships
}

void FireMissilesFixed(Board& board, const int num_missiles = 10) {
    // Fire missiles at fixed coordinates
    std::cout << "Firing " << num_missiles << " missiles at fixed coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before firing missiles
    int row = 1, col = 1, result, count = 0;
    for (int missile = 1; missile <= num_missiles; ++missile) {
        // Generate diagonal missile coordinates
        row = (row + 1) % board.Rows();
        col = (col + 2) % board.Cols();
        std::cout << "Firing missile #" << missile << " at " <<
            Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += result;
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        // Print board after half and all missiles have been fired
        if (num_missiles >= 4 && missile % (num_missiles / 2) == 0)
            board.Print();
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << num_missiles << " missiles at fixed coordinates (" <<
        count << " hit, " << num_missiles - count << " missed)" << std::endl;
    usleep(timestep);  // Sleep after firing all missiles
}

void FireMissilesRandom(Board& board, const int num_missiles = 10) {
    // Fire missiles at random coordinates
    std::cout << "Firing " << num_missiles << " missiles at random coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before firing missiles
    RandomGenerator random;
    int row, col, result, count = 0;
    for (int missile = 1; missile <= num_missiles; ++missile) {
        // Generate random missile coordinates
        row = random.RandomInt(0, board.Rows() - 1);
        col = random.RandomInt(0, board.Cols() - 1);
        std::cout << "Firing missile #" << missile << " at " <<
            Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += result;
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        // Print board after half and all missiles have been fired
        if (num_missiles >= 4 && missile % (num_missiles / 2) == 0)
            board.Print();
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << num_missiles << " missiles at random coordinates (" <<
        count << " hit, " << num_missiles - count << " missed)" << std::endl;
    usleep(timestep);  // Sleep after firing all missiles
}

void FireMissilesUser(Board& board, const int num_missiles = 10) {
    // Fire missiles at user-chosen coordinates
    std::cout << "Firing " << num_missiles << " missiles at user-chosen coordinates..." << std::endl;
    int row, col, result, count = 0;
    for (int missile = 1; missile <= num_missiles; ++missile) {
        std::cout << "Fire missile #" << missile << "..." << std::endl;
        std::cout << "Enter row:    ";
        std::cin >> row;
        std::cout << "Enter column: ";
        std::cin >> col;
        std::cout << "Firing missile at " << Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += result;
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        board.Print();
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << num_missiles << " missiles at user-chosen coordinates (" <<
        count << " hit, " << num_missiles - count << " missed)" << std::endl;
}

void TestPlayer(const Board& board) {
    // Test placing ships using orientation, size, and coordinates from player
    // Create a new Player with a default name
    const Player& player = Player(1, "Name");
    // Get board size from player
    std::cout << "Asking player for board size..." << std::endl;
    const int *size = player.GetBoardSize();
    std::cout << "Returned board size: " << size[0] << " rows, " <<
                                            size[1] << " columns" << std::endl;
    delete [] size;  // Delete heap-allocated array to avoid memory leak
    // Get ship orientation, size, and coordinates from player
    std::cout << "Asking player for ship placement..." << std::endl;
    const int *ship_coords = player.GetShipCoords(board);
    const std::string orientation = (ship_coords[3] == 1 ? "vertical" : "horizontal");
    std::cout << "Returned ship placement info: " << orientation << " ship with size " <<
        ship_coords[2] << " at " << Board::CoordStr(ship_coords[0], ship_coords[1]) << std::endl;
    delete [] ship_coords;  // Delete heap-allocated array to avoid memory leak
    // Get missile coordinates from player
    std::cout << "Asking player for missile coordinates..." << std::endl;
    const int *missile_coords = player.GetMissileCoords(board);
    std::cout << "Returned missile coordinates: " << Board::CoordStr(missile_coords[0], missile_coords[1]) << std::endl;
    delete [] missile_coords;  // Delete heap-allocated array to avoid memory leak
}

void PlaceShipsPlayer(Board& board, const Player& player, const int num_ships) {
    // Test placing ships using orientation, size, and coordinates from player
    std::cout << "Asking player to place " << num_ships << " ships..." << std::endl;
    usleep(timestep);  // Sleep before placing ships
    const int *ship_coords;  // Ship coordinates: (row, col, size, vertical)
    int row, col, size, vertical, result, count = 0;
    std::string orientation;
    for (int ship = 1; ship <= num_ships; ++ship) {
        // Get ship orientation, size, and coordinates from player
        ship_coords = player.GetShipCoords(board);
        // Unpack ship orientation, size, and coordinates from returned array
        row = ship_coords[0];
        col = ship_coords[1];
        size = ship_coords[2];
        vertical = ship_coords[3];
        orientation = (vertical ? "vertically" : "horizontally");
        std::cout << "Placing ship #" << ship << " with size " << size << " " <<
            orientation << " at " << Board::CoordStr(row, col);
        // Place ship at player-chosen coordinates
        if (vertical)
            result = board.PlaceShipVertical(row, row + size - 1, col);
        else
            result = board.PlaceShipHorizontal(row, col, col + size - 1);
        count += result;
        std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
        board.Print();
        usleep(timestep / 2);  // Sleep after placing ship
    }
    delete [] ship_coords;  // Delete heap-allocated array to avoid memory leak
    std::cout << "Player placed " << num_ships << " ships (" << count <<
        " succeeded, " << num_ships - count << " failed)" << std::endl << std::endl;
    usleep(timestep);  // Sleep after placing all ships
}

void FireMissilesPlayer(Board& board, const Player& player, const int num_missiles) {
    // Test firing missiles using coordinates from player
    std::cout << "Asking player to fire " << num_missiles << " missiles..." << std::endl;
    usleep(timestep);  // Sleep before firing missiles
    const int *missile_coords;  // Missile coordinates: (row, col)
    int row, col, result, count = 0;
    for (int missile = 1; missile <= num_missiles; ++missile) {
        // Get missile coordinates from player
        missile_coords = player.GetMissileCoords(board);
        // Unpack missile coordinates from returned array
        row = missile_coords[0];
        col = missile_coords[1];
        std::cout << "Firing missile #" << missile << " at " <<
            Board::CoordStr(row, col);
        // Fire missile at player-chosen coordinates
        result = board.FireMissile(row, col);
        count += result;
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        // Print board after half and all missiles have been fired
        if (num_missiles >= 4 && missile % (num_missiles / 2) == 0)
            board.Print();
        usleep(timestep / 4);  // Sleep after firing missile
    }
    delete [] missile_coords;  // Delete heap-allocated array to avoid memory leak
    std::cout << "Player fired " << num_missiles << " missiles (" << count <<
        " hit, " << num_missiles - count << " missed)" << std::endl << std::endl;
    usleep(timestep);  // Sleep after firing all missiles
}

void TestRandomPlayer() {
    // Create a new RandomPlayer with an apt name (Mersenne-Twister generator)
    // Must be a const reference to avoid slicing RandomPlayer object as Player
    const Player& player = RandomPlayer(1, "Mersenne");

    std::cout << "Asking player for board size..." << std::endl;
    usleep(timestep);  // Sleep before creating board
    // Get board size from player
    const int *size = player.GetBoardSize();  // Board size: (rows, cols)
    std::cout << "Created board with size: " << size[0] << " rows, " <<
                                                size[1] << " columns" << std::endl;
    // Create a new Board with player-chosen size
    Board board = Board(size[0], size[1]);
    delete [] size;  // Delete heap-allocated array to avoid memory leak
    board.Print();
    usleep(timestep);  // Sleep after creating board

    const int num_ships = board.Rows() * board.Cols() / 6;
    const int num_missiles = board.Rows() * board.Cols() / 4;
    // Place ships at player-chosen coordinates
    PlaceShipsPlayer(board, player, num_ships);
    // Fire missiles at player-chosen coordinates
    FireMissilesPlayer(board, player, num_missiles);
}

void TestBoardFixed() {
    // Create a new Board with fixed size
    const int rows = 6, cols = 8;
    Board board = Board(rows, cols);
    board.Print();
    // Place ships at fixed coordinates
    PlaceShipsFixed(board);
    // Fire missiles at fixed coordinates
    FireMissilesFixed(board);
}

void TestBoardRandom() {
    // Generate random integer for each dimension of board size
    RandomGenerator random;
    const int rows = random.RandomInt(3, 12);
    const int cols = random.RandomInt(4, 16);
    // Create a new Board with random size
    Board board = Board(rows, cols);
    board.Print();
    const int num_ships = board.Rows() * board.Cols() / 6;
    const int num_missiles = board.Rows() * board.Cols() / 4;
    // Place ships at random coordinates
    PlaceShipsRandom(board, num_ships);
    // Fire missiles at random coordinates
    FireMissilesRandom(board, num_missiles);
}

void TestBoardUser() {
    // Ask user for board size: (rows, columns)
    const int *size = AskUserForBoardSize();
    const int rows = size[0];
    const int cols = size[1];
    delete [] size;  // Delete heap-allocated array to avoid memory leak
    // Create a new Board with user-chosen size
    Board board = Board(rows, cols);
    board.Print();
    const int num_ships = board.Rows() * board.Cols() / 6;
    const int num_missiles = board.Rows() * board.Cols() / 4;
    // Place ships at user-chosen coordinates
    PlaceShipsUser(board, num_ships);
    // Fire missiles at user-chosen coordinates
    FireMissilesUser(board, num_missiles);
}

void TestGame() {
    // Create a new Game with 2 players
    Game game = Game(2);
    // Ask players to place ships on their board
    game.Init();
    // Ask players to fire missiles in turn until a player wins the game
    game.Play();
}

int main(int argc, const char * argv[]) {
    // TestBoardFixed();
    // TestBoardRandom();
    // TestBoardUser();
    // TestPlayer(board);
    // TestRandomPlayer();
    TestGame();
}
