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
    return attackPower;
}

bool BattleShip::isHit(int coordinate_x, int coordinate_y) {
  // true if ship was hit or not
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
  return health_ <= 0;
}

}  // namespace battleship
