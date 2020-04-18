#include <iostream>

#include "battleship/board.h"
#include "battleship/player.h"
#include "battleship/ship.h"
#include "battleship/game.h"

int main(int argc, char** argv) {

    // Init vars
    Game* game = battlleship::Game::CreateGame();
    game->Run();

    // print grid

}
