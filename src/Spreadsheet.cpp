#include "Spreadsheet.hpp"
#include <stdexcept>
#include <utility>
#include <iostream>

// basic implementation of the ctor
Spreadsheet::Spreadsheet(size_t width, size_t height) : m_width{width}, m_height{height} {
    m_cells = new SpreadsheetCell *[m_width];
    for (int i{0}; i < m_height; i++) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }
    std::cout << "normal constructor\n";
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
    std::cout << "destructor\n";
}

Spreadsheet::Spreadsheet(const Spreadsheet &source) : Spreadsheet{source.m_width, source.m_height} {
    for (size_t i{0}; i < m_width; i++) {
        for (int j = 0; j < m_height; ++j) {
            m_cells[i][j] = source.m_cells[i][j];
        }
    }
    std::cout << "copy constructor\n";
}

// this version is not exception free. If the allocation goes wrong, the object is corrupted.
// we need an all or nothing mechanism. It is called copy-and-swap.
Spreadsheet &Spreadsheet::operator=(const Spreadsheet &rhs) {
    // check for redundancy
    if (this == &rhs) {
        return *this;
    }

    // Free current memory
    for (int i{0}; i < m_width; i++) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;

    m_width = rhs.m_width;
    m_height = rhs.m_height;

    m_cells = new SpreadsheetCell *[m_width];
    for (int i{0}; i < m_height; i++) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }

    for (size_t i{0}; i < m_width; i++) {
        for (int j = 0; j < m_height; ++j) {
            m_cells[i][j] = rhs.m_cells[i][j];
        }
    }
    std::cout << "assignment operator\n";
    return *this;
}

void Spreadsheet::cleanup() noexcept {
    for (int i{0}; i < m_width; i++) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
    m_width = m_height = 0;
}

void Spreadsheet::moveFrom(Spreadsheet &src) noexcept {
    m_height = std::exchange(src.m_height, 0);
    m_width = std::exchange(src.m_width, 0);
    m_cells = std::exchange(src.m_cells, nullptr);

}

Spreadsheet::Spreadsheet(Spreadsheet &&src) noexcept {
    moveFrom(src);
    std::cout << "move constructor\n";
}

Spreadsheet &Spreadsheet::operator=(Spreadsheet &&rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    cleanup();
    moveFrom(rhs);
    std::cout << "move assignment\n";
    return *this;
}
