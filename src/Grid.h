#ifndef CPP_SAMPLES_GRID_H
#define CPP_SAMPLES_GRID_H

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

    T &at(int x, int y) {
        verifyCoordinates(x, y);
        return m_cells[x][y];
    }

    std::pair<int, int> returnSize() const {
        return std::pair<int, int>(m_height, m_width);
    }

    virtual ~Grid() = default;

private:
    int m_height{0};
    int m_width{0};
    std::vector<std::vector<T>> m_cells;

    void verifyCoordinates(int x, int y) const {
        if ((x > m_height) || (y > m_width)) {
            throw std::out_of_range("out of range access");
        }
    };
};


#endif
