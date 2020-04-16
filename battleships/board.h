#ifndef BOARD_H_
#define BOARD_H_

namespace board {

class Board {
    public:
        Board(const int rows, const int columns);
        double GRID[columns][rows]; 

        void placeShip(const int y_coordinate_max, const int x_coordinate_max)
}

} // namespace board

#endif //BOARD_H_