#ifndef BOARD_H_
#define BOARD_H_

#include <string>

namespace battleship {

class Board {
  public:
    Board(const int rows, const int cols);
    ~Board();
    bool PlaceShipVertical(const int row_start, const int row_end, const int col);
    bool PlaceShipHorizontal(const int row, const int col_start, const int col_end);
    bool FireMissile(const int row, const int col);
    bool IsInBounds(const int row, const int col) const;
    bool IsFull() const;
    const int Rows() const;
    const int Cols() const;
    const int * Size() const;
    static const std::string CoordStr(const int row, const int col);
    const std::string CellStr(const int row, const int col) const;
    void Print() const;

  private:
    const int rows_;
    const int cols_;
    // int grid_[][];  // 2D array of ints
    // We want to declare a contiguous 2D array but this throws a compiler error:
    // "array has incomplete element type 'int []'" here and in the constructor:
    // "only the first dimension of an allocated array may have dynamic size"

    // Instead we need to declare an array of pointers to scattered row arrays
    int **grid_;  // Array of pointers to rows, each row is an array of ints
};  // class Board

}  // namespace battleship

#endif  // BOARD_H_
