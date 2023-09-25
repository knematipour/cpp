#include "SpreadsheetCell.hpp"
#include <iostream>
#include <charconv>

// implementation of assignment operator
SpreadsheetCell &SpreadsheetCell::operator=(const SpreadsheetCell &rhs) {
    // to prevent copy unto itself
    if (this == &rhs) {
        return *this;
    }

    // always return *this
    m_value = rhs.m_value;
    return *this;
}

// copy constructor has access to the private data of the source object
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell &src) : m_value{src.m_value} {
    std::cout << "copy constructor is called!\n";
}

SpreadsheetCell::SpreadsheetCell(double d) : m_value{d} {
}

SpreadsheetCell::SpreadsheetCell(std::string_view s) {
    setString(s);
}

void SpreadsheetCell::setValue(double value) {
    m_value = value;
}

double SpreadsheetCell::getValue() const {
    return m_value;
}

void SpreadsheetCell::setString(std::string_view str) {
    m_value = stringToDouble(str);
}

std::string SpreadsheetCell::getString() const {
    return doubleToString(m_value);
}

std::string SpreadsheetCell::doubleToString(double d) const {
    return std::to_string(m_value);
}

double SpreadsheetCell::stringToDouble(std::string_view str) const {
    double number{0};
    std::from_chars(str.data(), str.data() + str.size(), number);
    return number;
}
