#include "game.h"

#include "vector"

namespace battleship {
    struct PlayerData {
        Player player_;
        Board board_; 

        PlayerData(Player& player, Board& board): player_(player), board_(board) {} 
    }

    Game* Game::CreateGame() {
        Game* game = new Game();
        game.AddPlayer();
        return game;
    }

    void Game::AddPlayer() {
        PlayerData data = PlayerData(Player(), Board());
        player_data_.push_back(data);
    }

    void Game::Run() {
        // make sure the game only runs until someone wins or loses
    }
}