#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>

#include "battleship.h"

namespace battleship {

class Player {
    
  private:
    int totalHealth;
    int numShips;
    bool isWon;
    bool isLoss;
    bool collision();
    std::vector<BattleShip> ships;
};

}  // namespace battleship

#endif
