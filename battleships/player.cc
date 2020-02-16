#include "battleship.h"
#include "player.h"

#include <string>
#include <vector>

namespace battleship {

Player::Player(const int totalHealth, const int gridSize ) {
    
    this->totalHealth = totalHealth;
   
    this->carrier = new BattleShip(10, 1, "Carrier");
    this->battleship = new BattleShip(5, 5, "Battleship");
    this->cruiser= new BattleShip(3, 2, "Cruiser");
    this->submarine = new BattleShip(2, 4, "Submarine");
    this->destroyer= new BattleShip(6, 7, "Destroyer");
    
}

bool isWon(){
    /*
     * This function returns true if the current
     * player is the last one to have above 0 health.
     */

    pass
}

bool isLoss(){
    /*
     * This function returns true if the current player'
     * health reaches 0.
     */

    pass
}

bool collision(){
    /*
     * This function returns true if given coordinates of block
     * do not collide with another block from (whether it is from
     * same ship or different ship)
     * /
}

} // namepace battleship
