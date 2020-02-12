#define BATTLESHIP_H_

#include "block.h"
#include <string>
#include <vector>

namespace Game {
namespace Ships {

class BattleShip {

  public:
    int health;
    std::string name;
    static int numOfShips;

  private:
    std::vector<Game::Map::Coordinate> coordinates;
    int getCoordinates();
    bool attack();
    bool isHit();
    bool collision();
    bool isSunk();
};

/* 
 * Carrier (5)
 * Battleship (4)
 * Cruiser (3)
 * Submarine (3)
 * Destroyer (2)
 * */

} // namespace Battleship
} // namespace Game
