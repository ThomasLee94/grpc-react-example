#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>

#include "battleship.h"

namespace battleship {

class Player {
    public:
        Player(const int totalHealth, const std::string name);
    
    private:
        int totalHealth;
        int numShips;

        BattleShip carrier;
        BattleShip battleship;
        BattleShip cruiser;
        BattleShip submarine;
        BattleShip destroyer;

        bool isWon();
        bool isLoss();
        bool collision();
        std::vector<BattleShip> ships;
};

}  // namespace battleship

#endif
