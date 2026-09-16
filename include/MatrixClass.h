#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <type_traits>
#include <vector>

template <typename T>
class MatrixClass {
    static_assert(std::is_same<T, int>::value || std::is_same<T, double>::value,
                  "MatrixClass supports only int and double.");

public:
    MatrixClass(int rows, int cols);

    int numRows() const;
    int numCols() const;

    T get(int row, int col) const;
    void set(int row, int col, T value);

    MatrixClass<T> add(const MatrixClass<T>& other) const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<T>> values_;
};

#endif
