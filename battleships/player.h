#ifndef PLAYER_H_
#include "battleship.h"
#include <string>
#include <vector>

namespace Game {
    class Player {
        
      private:
        int totalHealth;
        int numShips;
        bool isWon;
        bool isLoss;
        bool collision();
        std::vector<Game::Ships::Battleship> ships;
    };
}

#endif
