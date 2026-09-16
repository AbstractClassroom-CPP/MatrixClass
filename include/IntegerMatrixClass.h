#ifndef INTEGER_MATRIX_CLASS_H
#define INTEGER_MATRIX_CLASS_H

#include <vector>

class IntegerMatrixClass {
public:
    IntegerMatrixClass(int rows, int cols);

    int numRows() const;
    int numCols() const;

    int get(int row, int col) const;
    void set(int row, int col, int value);

    IntegerMatrixClass add(const IntegerMatrixClass& other) const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<int>> values_;
};

#endif
