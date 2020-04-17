#ifndef SHIP_H_
#define SHIP_H_

#include <string>
#include <vector>

#include "block.h"

namespace battleship {

class Ship {

  public:
    Ship(const int health, const std::string name);

    int attackPower_;

    bool attack();
    bool isHit(int coordinate_x, int coordinate_y);
    bool isSunk();

  private:
    int health_;
    std::string name_;
    std::vector<Block> blocks_;
};

}  // namespace battleship

#endif  // SHIP_H_
