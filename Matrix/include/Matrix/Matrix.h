
#pragma once

#include <cassert>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <type_traits>

namespace MatComp {

    struct Version {
        unsigned major;
        unsigned minor;
        unsigned patch;
    };
    const Version &getVersion();
    [[noreturn]] void die(const char *fileName, std::size_t lineNumber, const char *reason);

   template <typename Ty> class Matrix {

    static_assert(std::is_arithmetic<Ty>::value, "Matrix only accepts arithmetic (i.e. floating-point or integral) types.");

  public:
    constexpr Matrix() : numRows(0), numColumns(0), data(nullptr) {}

    Matrix(size_t rows, size_t cols) : numRows(rows), numColumns(cols) {
        allocate(rows * cols);
    }

    Matrix(size_t rows, size_t cols, Ty initialValue) : numRows(rows), numColumns(cols) {
        allocate(rows * cols);
        std::fill(data.get(), data.get() + (rows * cols), initialValue);
    }

/// Construct a \p numRows x \p numColumns Matrix with all elements
/// initialized to value \p val.
Matrix(size_t numRows, size_t numCols, Ty val) : Matrix(numRows, numCols) {
    allocate(getNumElements());
    for (size_t i = 0; i < getNumElements(); i++)
        data[i] = val;
}
    operator bool() const {
        return numRows != 0 && numColumns != 0;
    }

/// Access Matrix element at (\p row, \p col) by reference.
Ty &get(size_t row, size_t col) {
    assert(*this && "Invalid Matrix");
    assert(row < numRows && "Out of bounds row access");
    assert(col < numColumns && "Out of bounds column access");
    return data[row * numColumns + col];
}
/// Access Matrix element at (\p row, \p col) by reference (const version).
const Ty &get(size_t row, size_t col) const {
    assert(*this && "Invalid Matrix");
    assert(row < numRows && "Out of bounds row access");
    assert(col < numColumns && "Out of bounds column access");
    return data[row * numColumns + col];
}

    size_t getNumRows() const { return numRows; }
    size_t getNumColumns() const { return numColumns; }
    size_t getNumElements() const { return numRows * numColumns; }

    size_t getSizeInBytes() const { return numRows * numColumns * sizeof(Ty); }

  private:
    size_t numRows;
    size_t numColumns;
    std::unique_ptr<Ty[]> data;

    void allocate(size_t numElements) {
        if (numElements != 0) {
            data = std::make_unique<Ty[]>(numElements);
            if (!data)
                die(__FILE__, __LINE__, "Matrix allocation failure");
        }
    }
};

}
