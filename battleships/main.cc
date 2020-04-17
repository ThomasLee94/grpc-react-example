#include <iostream>

#include "battleships/board.h"

int main(int argc, char** argv) {
  /*
  Player player_1(16, 16);
  Player player_2(16, 16);

  Ship destroyer(5, Ship::VERTICAL);
  player_1.Place(5, 0, destroyer);

  while (!player_1.all_ships_are_sunk() && !player_2.all_ships_are_sunk()) {
    // TODO(tom): take input
    AttackResult result = player_1.Attack(input_x, input_y);
    if (result.hit_something) {
      std::cout << "Spot was hit!";
    }
    if (result.sunk_ship) {
      std::cout << "Ship was sunk!";
    }

    // TODO(tom): take input
    AttackResult result = player_2.Attack(input_x, input_y);
    if (result.hit_something) {
      std::cout << "Spot was hit!";
    }
    if (result.sunk_ship) {
      std::cout << "Ship was sunk!";
    }
  }

  if (player_1.all_ships_are_sunk()) {
    std::cout << "Player 2 wins";
  } else {
    std::cout << "Player 1 wins";
  }
  */

    // Init vars
    Board board(10, 10)
    Player player_1(5, "tom")
    Player player_2(5, "cenz")

    // print grid
    void print_grid() {
        cout << "  0 0 0 0 0 0 0 0 0  " << endl;
        cout << "---------------------" << endl;

        for (int y = 0 ; y < columns, y++) {
            for (int x = 0; x < rows; x++) {
                cout << GRID[y][x] << "";
            }
            cout << endl;
        }
    }

    bool MakeMove() {
      
    }
}
