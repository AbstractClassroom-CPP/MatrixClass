#include "MatrixClass.h"

#include <stdexcept>

template <typename T>
MatrixClass<T>::MatrixClass(int rows, int cols)
    : rows_(rows), cols_(cols), values_(rows, std::vector<T>(cols, T{})) {
}

template <typename T>
int MatrixClass<T>::numRows() const {
    return rows_;
}

template <typename T>
int MatrixClass<T>::numCols() const {
    return cols_;
}

template <typename T>
T MatrixClass<T>::get(int row, int col) const {
    return values_.at(row).at(col);
}

template <typename T>
void MatrixClass<T>::set(int row, int col, T value) {
    values_.at(row).at(col) = value;
}

template <typename T>
MatrixClass<T> MatrixClass<T>::add(const MatrixClass<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices must have the same dimensions.");
    }

    MatrixClass<T> result(rows_, cols_);
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            result.set(row, col, get(row, col) + other.get(row, col));
        }
    }
    return result;
}

// Build both supported types from the same implementation.
template class MatrixClass<int>;
template class MatrixClass<double>;
