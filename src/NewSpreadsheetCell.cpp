#include "NewSpreadsheetCell.h"
#include <string>
#include <sstream>
#include <charconv>


void StringSpreadsheetCell::set(std::string value) {
    m_value = value;
}

std::string StringSpreadsheetCell::getString() const {
    return m_value.value_or("");
}

void DoubleSpreadsheetCell::set(std::string value) {
    m_value = stringTodouble(value);
}

std::string DoubleSpreadsheetCell::doubleTostring(double value) {
    return std::to_string(value);
}

double DoubleSpreadsheetCell::stringTodouble(std::string value) {
    double res{};
    std::from_chars(value.data(), value.data() + value.size(), res);
    return res;
}

void DoubleSpreadsheetCell::set(double value) {
    m_value = value;
}

std::string DoubleSpreadsheetCell::getString() const {
    // std::string res = doubleTostring(m_value.value_or(0)); also works!
    return (m_value.has_value() ? doubleTostring(m_value.value()) : "");
}

