#ifndef BOARD_H_
#define BOARD_H_

namespace battleship {

class Board {
    public:
        Board(const int rows, const int columns);
        void PlaceShipVert(
            const int y_start, const int y_end, 
            const int x_start, 
            const int player);
        void PlaceShipHorizontal(
            const int y_start,
            const int x_start, const int x_end, 
            const int player);
        bool FireMissile(const int y, const int x, const int player);
        
        Ship carrier;
        Ship battleship;
        Ship cruiser;
        Ship submarine;
        Ship destroyer;

    
    private:
        double grid_[columns][rows]; 

}

} // namespace board

#endif //BOARD_H_