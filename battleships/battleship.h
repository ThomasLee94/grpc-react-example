#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include "block.h"
#include <string>
#include <vector>

class BattleShip {

  public:
    int health;
    std::string name;
    static numOfShips;

  private:
    std::vector<block> blocks;
    bool getCoordinates();
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
