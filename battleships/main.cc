#include <iostream>

#include "battleships/board.h"
#include "battleships/player.h"
#include "battleships/ship.h"
#include "battleships/gamemanager.h"

int main(int argc, char** argv) {

    // Init vars
    Game* game = battlleship::Game::CreateGame(); 
    game->Run();

    // print grid
   
}
