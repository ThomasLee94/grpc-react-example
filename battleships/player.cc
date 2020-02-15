#include "battleship.h"
#include "player.h"

#include <string>
#include <vector>

namespace battleship {

Player::Player(const int totalHealth, const int gridSize ) {
    
    this->totalHealth = totalHealth;
   
    carrier = new BattleShip(10, 1, "Carrier");
    battleship = new BattleShip(5, 5, "Battleship");
    cruiser= new BattleShip(3, 2, "Cruiser");
    submarine = new BattleShip(2, 4, "Submarine");
    destroyer= new BattleShip(6, 7, "Destroyer");
    
}

} // namepace battleship
