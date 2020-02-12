#define PLAYER_H_
#include <string>

class Player {
    
  private:
    int totalHealth;
    int numShips;
    bool isWon;
    bool isLoss;
    bool collision();
    std::vector<Battleships> ships;
}
