#include "game.h"

#include <unistd.h>  // Need usleep function (Unix systems only: Mac and Linux)
#include <iostream>
#include <vector>
#include <string>

static const int timestep = 0.5e6;  // Delay to use when sleeping: 1e6 = 1 second

namespace battleship {

Game::Game(const int num_players) {
    num_players_ = num_players;
    current_player_ = 0;
    is_started_ = false;
    is_won_ = false;
    // Initialize vectors of pointers to Player and Board objects
    players_ = std::vector<Player*>();
    boards_ = std::vector<Board*>();
    // Loop over player IDs to initialize each Player and Board object
    for (int player_id = 0; player_id < num_players_; ++player_id) {
        // Create a new RandomPlayer with an apt name (Mersenne-Twister generator)
        const std::string name = (player_id == 0 ? "Mersenne" : "Matsumoto");
        // Must be reference or pointer to avoid slicing RandomPlayer object as Player
        Player *player = new RandomPlayer(player_id, name);
        players_.push_back(player);
        // Get board size from player: (rows, cols)
        std::cout << "Asking " << player->Name() << " for board size..." << std::endl;
        usleep(timestep / 2);  // Sleep before creating board
        const int *size = player->GetBoardSize();
        std::cout << "Created board with size: " << size[0] << " rows, " <<
                                                    size[1] << " columns" << std::endl;
        // Create a new Board with player-chosen size
        Board *board = new Board(size[0], size[1]);
        delete [] size;  // Delete heap-allocated array to avoid memory leak
        boards_.push_back(board);
        board->Print();
        usleep(timestep);  // Sleep after creating board
    }
}

Game::~Game() {
    // Delete heap-allocated Player and Board objects to avoid memory leak
    for (auto player : players_)
        delete player;
    for (auto board : boards_)
        delete board;
}

void Game::Init() {
    // Prevent re-initializing game after it has started
    if (IsStarted())
        return;
    // Loop over player IDs and ask each player to place ships on their board
    for (int player_id = 0; player_id < num_players_; ++player_id) {
        const Player& player = *players_.at(player_id);
        Board& board = *boards_.at(player_id);
        const int num_ships = board.Rows() * board.Cols() / 6;
        std::cout << "Asking " << player.Name() << " to place " << num_ships << " ships..." << std::endl;
        usleep(timestep);  // Sleep before placing ships
        int row, col, size, vertical, result;
        std::string orientation;
        for (int ship = 1; ship <= num_ships; ) {
            // Get ship placement info from player: (row, col, size, vertical)
            const int *ship_coords = player.GetShipCoords(board);
            // Unpack ship orientation, size, and coordinates from returned array
            row = ship_coords[0];
            col = ship_coords[1];
            size = ship_coords[2];
            vertical = ship_coords[3];
            delete [] ship_coords;  // Delete heap-allocated array to avoid memory leak
            orientation = (vertical ? "vertically" : "horizontally");
            std::cout << "Placing ship #" << ship << " with size " << size <<
                " " << orientation << " at " << Board::CoordStr(row, col);
            // Place ship at player-chosen coordinates
            if (vertical)
                result = board.PlaceShipVertical(row, row + size - 1, col);
            else
                result = board.PlaceShipHorizontal(row, col, col + size - 1);
            ship += result;  // Advance to next ship only if placement succeeded
            std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
            board.Print();
            usleep(timestep / 2);  // Sleep after placing ship
        }
        std::cout << player.Name() << " placed " << num_ships << " ships" << std::endl << std::endl;
        usleep(2 * timestep);  // Sleep after placing all ships
    }
    is_started_ = true;
}

void Game::Play() {
    // Ask current player to fire missiles in turn until a player wins the game
    while (!IsWon()) {
        // Calculate ID of next player after current player
        const int next_player = (current_player_ + 1) % num_players_;
        const Player& player = *players_.at(current_player_);  // Current player
        Board& board = *boards_.at(next_player);  // Fire at next player's board
        // Ask current player for coordinates to fire missile on opponent's board
        std::cout << "Asking " << player.Name() << " to fire missile..." << std::endl;
        usleep(timestep / 2);  // Sleep before firing missile
        // Get missile coordinates from player: (row, col)
        const int *missile_coords = player.GetMissileCoords(board);
        // Unpack missile coordinates from returned array
        const int row = missile_coords[0];
        const int col = missile_coords[1];
        delete [] missile_coords;  // Delete heap-allocated array to avoid memory leak
        std::cout << "Firing missile at " << Board::CoordStr(row, col);
        // Fire missile at player-chosen coordinates
        const bool result = board.FireMissile(row, col);
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        board.Print();
        // usleep(timestep / 2);  // Sleep after firing missile
        // Check if opponent's board is full
        if (board.IsFull()) {
            // TODO: Determine if a player has won the game
            std::cout << "GAME OVER: " << player.Name() << " won the game!!!" << std::endl;
            is_won_ = true;
            break;
        }
        // Advance turn to next player
        current_player_ = next_player;
    }
}

const int Game::NumPlayers() const {
    return num_players_;
}

const int Game::CurrentPlayer() const {
    return current_player_;
}

const bool Game::IsStarted() const {
    return is_started_;
}

const bool Game::IsWon() const {
    return is_won_;  // TODO: Determine if a player has won the game
}

const int Game::Winner() const {
    if (IsWon()) {
        // Assume current player won the game (fired last missile to win)
        return current_player_;
    }
    return -1;  // No winner
}

}  // namespace battleship
