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

        const Board* board;

        bool IsWon();
        bool IsLoss();
        std::vector<BattleShip> ships;
};

}  // namespace battleship

#endif
