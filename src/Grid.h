#ifndef CPP_SAMPLES_GRID_H
#define CPP_SAMPLES_GRID_H

#include <optional>
#include <stdexcept>
#include <vector>

template<typename T>
class Grid {
public:
    explicit Grid(int h, int w) : m_height{h}, m_width{w} {
        m_cells.resize(m_width);
        for (int i = 0; i < m_width; ++i) {
            m_cells[i].resize(m_height);
        }
    }


    Grid(const Grid &source) = default; // copy constructor
    Grid &operator=(const Grid &rhs) = default; // assignment operator

    Grid(const Grid &&source) = default; // move constructor
    Grid &operator=(const Grid &&rhs) = default; // move assignment


    const std::optional<T> &at(int x, int y) const {
        verifyCoordinates(x, y);
        return m_cells[x][y];
    }

    // very interesting
    // Scott Meyers' const_cast pattern
    // this is done to have a const and non-const version of the same function
    std::optional<T> &at(int x, int y) {
        return const_cast<std::optional<T> &>(std::as_const(*this).at(x, y));
    }

    std::pair<int, int> returnSize() const {
        return std::pair<int, int>(m_height, m_width);
    }

    virtual ~Grid() = default;

private:
    int m_height{0};
    int m_width{0};
    std::vector<std::vector<std::optional<T>>> m_cells;

    void verifyCoordinates(int x, int y) const {
        if ((x > m_height) || (y > m_width)) {
            throw std::out_of_range("out of range access");
        }
    };
};


template<typename T, size_t height, size_t width>
class OtherGrid {
public:
    OtherGrid() = default;

    OtherGrid(const OtherGrid &source) = default; // copy constructor
    OtherGrid &operator=(const OtherGrid &rhs) = default; // assignment operator

    // C-Style Arrays don't support move semantics
    // OtherGrid(const OtherGrid &&source) = default; // move constructor
    // OtherGrid &operator=(const OtherGrid &&rhs) = default; // move assignment


    const std::optional<T> &at(int x, int y) const {
        verifyCoordinates(x, y);
        return m_cells[x][y];
    }

    std::optional<T> &at(int x, int y) {
        return const_cast<std::optional<T> &>(std::as_const(*this).at(x, y));
    }

    std::pair<int, int> returnSize() const {
        return std::pair<int, int>(height, width);
    }

    virtual ~OtherGrid() = default;

private:
    std::optional<T> m_cells[height][width];

    void verifyCoordinates(int x, int y) const {
        if ((x > height) || (y > width)) {
            throw std::out_of_range("out of range access");
        }
    };
};


// this is a template Specialization for OtherGrid class that handles std::string
template<>
template<size_t h, size_t w>
class OtherGrid<std::string, h, w> {
    // code omitted for brevity
};

// aliasing a template
using myGrid = OtherGrid<int, 5, 5>;


#endif
