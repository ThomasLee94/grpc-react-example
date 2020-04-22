#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include "player.h"
#include "board.h"

namespace battleship {

class Game {
  public:
    Game(const int num_players = 2);
    ~Game();
    void Init();
    void Play();
    const int NumPlayers() const;
    const int CurrentPlayer() const;
    const bool IsStarted() const;
    const bool IsWon() const;
    const int Winner() const;

  private:
    int num_players_;
    int current_player_;
    bool is_started_;
    bool is_won_;
    std::vector<Player*> players_;
    std::vector<Board*> boards_;
};  // class Game

}  // namespace battleship

#endif  // GAME_H_
