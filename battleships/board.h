#ifndef BOARD_H_
#define BOARD_H_

namespace board {

class Board {
    public:
        Board(const int rows, const int columns);
        void placeShipVert(
            const int y_start, const int y_end, 
            const int x_start, const int x_end, 
            const int player);
        void placeShipHorizontal(
            const int y_start, const int y_end, 
            const int x_start, const int x_end, 
            const int player);
        bool fireMissile(const int y, const int x, const int player);
    
    private:
        double grid_[columns][rows]; 

}

} // namespace board

#endif //BOARD_H_