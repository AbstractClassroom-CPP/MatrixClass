#ifndef DOUBLE_MATRIX_CLASS_H
#define DOUBLE_MATRIX_CLASS_H

#include <vector>

class DoubleMatrixClass {
public:
    DoubleMatrixClass(int rows, int cols);

    int numRows() const;
    int numCols() const;

    double get(int row, int col) const;
    void set(int row, int col, double value);

    DoubleMatrixClass add(const DoubleMatrixClass& other) const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<double>> values_;
};

#endif
