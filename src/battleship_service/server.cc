#include <memory>
#include <string>
#include <iostream>

#include "src/battleship_game/game.h"


int main(int argc, char** argv) {
  battleship::Game game;
  std::cout << game.IsStarted(); 
  return 0;
}