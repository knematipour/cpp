#pragma once

#include "SpreadsheetCell.hpp"
#include <cstddef>

// We need to provide copy and assignment operator overload since pointers are shallow copied and 
// if not overridden, can create "Dangling Pointer" problem. That means when an object is passed to
// a function, the copied object in the function will get a pointer to the object's data and may free
// it hence, invalidating the memoty of the main object. 

class Spreadsheet {
public:
    Spreadsheet(size_t width, size_t height);

    void setCellAt(size_t x, size_t y, const SpreadsheetCell &cell);

    SpreadsheetCell &getCellAt(size_t x, size_t y);

    ~Spreadsheet();

private:
    void verifyCoordinates(size_t x, size_t y) const;

    size_t m_width{0};
    size_t m_height{0};
    SpreadsheetCell **m_cells{nullptr};
};