#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "ship.h" 
#include "player.h"
#include "board.h"

#include <vector>

namespace battleship {

class GameManager {
    GameManager* CreateGame();

    public:
        void AddPlayer();

    private:
        std::vector<PlayerData> player_data_;
        Board board;
        Ship ship;
        Player player;
        void Run();
}
}

#endif