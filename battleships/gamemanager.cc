#include "gamemanager.h"

#include "vector"

namespace battleship {
    struct PlayerData {
        Player player_;
        Board board_; 

        PlayerData(Player& player, Board& board): player_(player), board_(board) {} 
    }

    GameManager* GameManager::CreateGame() {
        GameManager* manager = new GameManager();
        manager.AddPlayer();
        return manager;
    }

    void GameManager::AddPlayer() {
        PlayerData data = PlayerData(Player(), Board());
        player_data_.push_back(data);
    }
}