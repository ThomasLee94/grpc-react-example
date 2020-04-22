#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "board.h"

namespace battleship {

class Player {
  public:
    Player(const int id, const std::string name);
    const int ID() const;
    const std::string Name() const;
    virtual const int * GetBoardSize() const;
    virtual const int * GetShipCoords(const Board& board) const;
    virtual const int * GetMissileCoords(const Board& board) const;

  private:
    const int id_;
    const std::string name_;
};  // class Player

class RandomPlayer : public Player {
  public:
    RandomPlayer(const int id, const std::string name);
    const int * GetBoardSize() const;
    const int * GetShipCoords(const Board& board) const;
    const int * GetMissileCoords(const Board& board) const;

  private:
    const int id_;
    const std::string name_;
};  // class RandomPlayer

}  // namespace battleship

#endif  // PLAYER_H_
