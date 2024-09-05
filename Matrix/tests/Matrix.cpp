#include "Matrix/Matrix.h"

#include "gtest/gtest.h"

#include <cstdint>

using MatComp::Matrix;

TEST(Matrix, defaultConstruct) {
    Matrix<int8_t> m0;
    EXPECT_FALSE(m0);
	EXPECT_EQ(m0.getNumRows(), 0);
    EXPECT_EQ(m0.getNumColumns(), 0);
    EXPECT_EQ(m0.getNumElements(), 0);
    EXPECT_EQ(m0.getSizeInBytes(), 0);

    Matrix<float> m1;
    EXPECT_FALSE(m1);
EXPECT_EQ(m1.getNumRows(), 0);
    EXPECT_EQ(m1.getNumColumns(), 0);
    EXPECT_EQ(m1.getNumElements(), 0);
    EXPECT_EQ(m1.getSizeInBytes(), 0);
}

TEST(Matrix, booleanConversion) {
    EXPECT_FALSE(Matrix<int8_t>());
    EXPECT_FALSE(Matrix<double>());

    EXPECT_TRUE(Matrix<int8_t>(1, 1));
    EXPECT_TRUE(Matrix<double>(1, 1));

    EXPECT_TRUE(Matrix<int8_t>(1, 1, 1));
    EXPECT_TRUE(Matrix<double>(1, 1, 2.0));
}

TEST(Matrix, uninitializedConstruct) {
    Matrix<int16_t> m0(2, 3);
    EXPECT_TRUE(m0);
    EXPECT_EQ(m0.getNumRows(), 2);
    EXPECT_EQ(m0.getNumColumns(), 3);
    EXPECT_EQ(m0.getNumElements(), 6);
    EXPECT_EQ(m0.getSizeInBytes(), 6 * sizeof(int16_t));

    Matrix<double> m1(3, 4);
    EXPECT_TRUE(m1);
    EXPECT_EQ(m1.getNumRows(), 3);
    EXPECT_EQ(m1.getNumColumns(), 4);
    EXPECT_EQ(m1.getNumElements(), 12);
    EXPECT_EQ(m1.getSizeInBytes(), 12 * sizeof(double));
}
TEST(Matrix, fillConstruct) {
    Matrix<uint32_t> m0(2, 2, 13);
    EXPECT_TRUE(m0);
    EXPECT_EQ(m0.getNumRows(), 2);
    EXPECT_EQ(m0.getNumColumns(), 2);
    EXPECT_EQ(m0.getNumElements(), 4);
    EXPECT_EQ(m0.getSizeInBytes(), 4 * sizeof(uint32_t));
    for (size_t row = 0; row < m0.getNumRows(); row++)
        for (size_t col = 0; col < m0.getNumColumns(); col++)
            EXPECT_EQ(m0.get(row, col), uint32_t(13));

    Matrix<double> m1(2, 2, 16.0);
    EXPECT_TRUE(m1);
    EXPECT_EQ(m1.getNumRows(), 2);
    EXPECT_EQ(m1.getNumColumns(), 2);
    EXPECT_EQ(m1.getNumElements(), 4);
    EXPECT_EQ(m1.getSizeInBytes(), 4 * sizeof(double));
    for (size_t row = 0; row < m1.getNumRows(); row++)
        for (size_t col = 0; col < m1.getNumColumns(); col++)
            EXPECT_EQ(m1.get(row, col), double(16.0));
}

TEST(Matrix, getElement) {
    Matrix<uint32_t> m0(2, 3, 3);
    EXPECT_TRUE(m0);
    for (size_t row = 0; row < m0.getNumRows(); row++)
        for (size_t col = 0; col < m0.getNumColumns(); col++)
            EXPECT_EQ(m0.get(row, col), 3);
}

TEST(Matrix, setElement) {
    Matrix<uint32_t> m0(2, 3, 3);
    EXPECT_TRUE(m0);
    for (size_t row = 0; row < m0.getNumRows(); row++)
        for (size_t col = 0; col < m0.getNumColumns(); col++)
            EXPECT_EQ(m0.get(row, col), 3);
    m0.get(1, 2) = 65;
    for (size_t row = 0; row < m0.getNumRows(); row++)
        for (size_t col = 0; col < m0.getNumColumns(); col++)
            if (row == 1 && col == 2)
                EXPECT_EQ(m0.get(row, col), 65);
            else
                EXPECT_EQ(m0.get(row, col), 3);
}
