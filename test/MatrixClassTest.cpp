#include "MatrixClass.h"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(MatrixClassTest, StartsWithRequestedDimensionsAndZeroValues) {
    MatrixClass<int> integers(2, 3);
    MatrixClass<double> doubles(2, 3);

    EXPECT_EQ(integers.numRows(), 2);
    EXPECT_EQ(integers.numCols(), 3);
    EXPECT_EQ(doubles.numRows(), 2);
    EXPECT_EQ(doubles.numCols(), 3);

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            EXPECT_EQ(integers.get(row, col), 0);
            EXPECT_DOUBLE_EQ(doubles.get(row, col), 0.0);
        }
    }
}

TEST(MatrixClassTest, SetsAndGetsValues) {
    MatrixClass<int> integers(2, 3);
    MatrixClass<double> doubles(2, 3);

    integers.set(1, 2, -7);
    doubles.set(1, 2, 1.25);

    EXPECT_EQ(integers.get(1, 2), -7);
    EXPECT_DOUBLE_EQ(doubles.get(1, 2), 1.25);
    EXPECT_EQ(integers.get(0, 0), 0);
    EXPECT_DOUBLE_EQ(doubles.get(0, 0), 0.0);
}

TEST(MatrixClassTest, AddsIntegersWithoutChangingInputs) {
    MatrixClass<int> a(2, 3);
    MatrixClass<int> b(2, 3);
    a.set(0, 1, 4);
    b.set(0, 1, 2);
    a.set(1, 2, -3);
    b.set(1, 2, 1);

    const MatrixClass<int> c = a.add(b);

    EXPECT_EQ(c.numRows(), 2);
    EXPECT_EQ(c.numCols(), 3);
    EXPECT_EQ(c.get(0, 1), 6);
    EXPECT_EQ(c.get(1, 2), -2);
    EXPECT_EQ(c.get(0, 0), 0);
    EXPECT_EQ(a.get(0, 1), 4);
    EXPECT_EQ(b.get(0, 1), 2);
    EXPECT_EQ(a.get(1, 2), -3);
    EXPECT_EQ(b.get(1, 2), 1);
}

TEST(MatrixClassTest, AddsDoublesWithoutChangingInputs) {
    MatrixClass<double> a(2, 3);
    MatrixClass<double> b(2, 3);
    a.set(0, 1, 0.1);
    b.set(0, 1, 0.2);
    a.set(1, 2, -1.25);
    b.set(1, 2, 0.5);

    const MatrixClass<double> c = a.add(b);

    EXPECT_EQ(c.numRows(), 2);
    EXPECT_EQ(c.numCols(), 3);
    EXPECT_NEAR(c.get(0, 1), 0.3, 1e-12);
    EXPECT_NEAR(c.get(1, 2), -0.75, 1e-12);
    EXPECT_DOUBLE_EQ(c.get(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(a.get(0, 1), 0.1);
    EXPECT_DOUBLE_EQ(b.get(0, 1), 0.2);
    EXPECT_DOUBLE_EQ(a.get(1, 2), -1.25);
    EXPECT_DOUBLE_EQ(b.get(1, 2), 0.5);
}

TEST(MatrixClassTest, RejectsMismatchedDimensions) {
    MatrixClass<int> integers(2, 3);
    MatrixClass<double> doubles(2, 3);

    EXPECT_THROW(integers.add(MatrixClass<int>(3, 3)), std::invalid_argument);
    EXPECT_THROW(integers.add(MatrixClass<int>(2, 4)), std::invalid_argument);
    EXPECT_THROW(doubles.add(MatrixClass<double>(3, 3)), std::invalid_argument);
    EXPECT_THROW(doubles.add(MatrixClass<double>(2, 4)), std::invalid_argument);
}

TEST(MatrixClassTest, RejectsInvalidIndices) {
    MatrixClass<int> integers(2, 3);
    MatrixClass<double> doubles(2, 3);

    EXPECT_THROW(integers.get(-1, 0), std::out_of_range);
    EXPECT_THROW(integers.get(2, 0), std::out_of_range);
    EXPECT_THROW(integers.set(0, -1, 7), std::out_of_range);
    EXPECT_THROW(integers.set(0, 3, 7), std::out_of_range);
    EXPECT_THROW(doubles.get(-1, 0), std::out_of_range);
    EXPECT_THROW(doubles.get(2, 0), std::out_of_range);
    EXPECT_THROW(doubles.set(0, -1, 1.25), std::out_of_range);
    EXPECT_THROW(doubles.set(0, 3, 1.25), std::out_of_range);
}
