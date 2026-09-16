#include "DoubleMatrixClass.h"

#include <stdexcept>

DoubleMatrixClass::DoubleMatrixClass(int rows, int cols)
    : rows_(rows), cols_(cols), values_(rows, std::vector<double>(cols, 0.0)) {
}

int DoubleMatrixClass::numRows() const {
    return rows_;
}

int DoubleMatrixClass::numCols() const {
    return cols_;
}

double DoubleMatrixClass::get(int row, int col) const {
    return values_.at(row).at(col);
}

void DoubleMatrixClass::set(int row, int col, double value) {
    values_.at(row).at(col) = value;
}

DoubleMatrixClass DoubleMatrixClass::add(const DoubleMatrixClass& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices must have the same dimensions.");
    }

    DoubleMatrixClass result(rows_, cols_);
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            result.set(row, col, get(row, col) + other.get(row, col));
        }
    }
    return result;
}
