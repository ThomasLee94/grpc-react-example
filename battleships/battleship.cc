#include "battleship.h"
#include <string>
#include <tuple>
#include <vector>

namespace Game {
namespace Ships {

// Constructor
Battleship(
    const int health, const string name, const int attackPower)
        : health_(health), name_(name), attackPower_(attackPower),
          blocks_(std::vector<block>()) {}

// Private Functions

int Battleship::getCoordinates() {
  // return coordinates of the individual blocks
}

// Public Functions
bool Battleship::isHit(int coordinate_x, int coordinate_y) {
  // true if ship was hit or not
  if (Battleship::block::coordinate_x == coordinate_x) {
    if (Battleship::block::coordinate_y == coordinate_y) {
      return true
    }
  }

  return false

}

bool Battleship::collision() {
  // checks whether ships are colliding or not
}

bool Battleship::isSunk() {
  return Battleship::health_ <= 0;
}

} // Battlship
} // Game