#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <string>
#include <vector>

#include "block.h"

namespace battleship {

class BattleShip {

  public:
    BattleShip(const int health, const std::string name);

    bool attack();
    bool isHit(int coordinate_x, int coordinate_y);
    bool collision();
    bool isSunk();

  private:
    int health_;
    std::string name_;
    std::vector<Block> blocks_;
};

/* 
 * Carrier (5)
 * Battleship (4)
 * Cruiser (3)
 * Submarine (3)
 * Destroyer (2)
 * */

}  // namespace battleship

#endif  // BATTLESHIP_H_
