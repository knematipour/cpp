#include "Spreadsheet.hpp"
#include <stdexcept>

// basic implementation of the ctor
Spreadsheet::Spreadsheet(size_t width, size_t height) : m_width{width}, m_height{height} {
    m_cells = new SpreadsheetCell *[m_width];
    for (int i{0}; i < m_height; i++) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }
}

void Spreadsheet::verifyCoordinates(size_t x, size_t y) const {
    if (x >= m_width) {
        throw std::out_of_range("X is out of range!");
    }

    if (y >= m_height) {
        throw std::out_of_range("Y is out of range!");
    }
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell &cell) {
    verifyCoordinates(x, y);
    m_cells[x][y] = cell;
}

SpreadsheetCell &Spreadsheet::getCellAt(size_t x, size_t y) {
    verifyCoordinates(x, y);
    return m_cells[x][y];
}

Spreadsheet::~Spreadsheet() {
    for (int i{0}; i < m_width; i++) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
}