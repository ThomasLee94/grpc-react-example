#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <vector>

#include "ship.h" 
#include "player.h"
#include "board.h"

namespace battleship {

class Game {
    Game* CreateGame();

    public:
        void AddPlayer();
        std::string ShowBoard();

    private:
        std::vector<PlayerData> player_data_;
        Board board;
        Ship ship;
        Player player;
        void Run();
}
}

#endif