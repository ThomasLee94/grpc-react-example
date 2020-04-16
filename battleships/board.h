#ifndef BOARD_H_
#define BOARD_H_

namespace board {

class Board {
    public:
        Board(const int rows, const int columns);
        void placeShip(const int y_coordinate_max, const int x_coordinate_max);
        bool fireMissile(const int y_coordinate, const int x_coordinate);
    
    private:
        double grid_[columns][rows]; 

}

} // namespace board

#endif //BOARD_H_