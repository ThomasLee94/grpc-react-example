#include "battleship.h"

#include <string>
#include <tuple>
#include <vector>

namespace battleship {

// Constructor
BattleShip::BattleShip(const int health, const int attackPower, const std::string name)
    : health_(health), attackPower_(attackPower), name_(name), blocks_(std::vector<Block>()) {}

// Public Functions
int attack() {
    /* 
     * This function returns the attack power of
     * the current instance of class "BattleShips"
     */
    return attackPower_;
}

bool BattleShip::isHit(int coordinate_x, int coordinate_y) {
    /*
     * This function returns a bool; if the co-ordinates
     * match a hit it returns true. Otherwise it returns
     * false.
     */
    for (const Block& block : blocks_) {
    if (block.coordinate_x == coordinate_x) {
      if (block.coordinate_y == coordinate_y) {
        return true;
      }
    }
  }

  return false;
}

bool BattleShip::isSunk() {
    /*
     * This function returns true if health of current instance
     * of battleship lowers to 0.
     */
    return health_ <= 0;
}

}  // namespace battleship
