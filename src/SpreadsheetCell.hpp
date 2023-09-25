#pragma once

#include <string>

class SpreadsheetCell {
public:
    // changed for providing multiple constructors
    // defauld constructor is provided ONLY when no constructor is defined!
    // The problem called Most Vexing Parse
    SpreadsheetCell() = default; // adds a compiler-generated default constructor to the class
    // convertor constructor, can be marked explicit
    SpreadsheetCell(double initialValue);

    SpreadsheetCell(std::string_view initialValue);

    // copy constructor is called when object is passed by value to a function
    // Also called when object is returned by value from a function
    // Also called when the compiler creates temporary objects(?)
    // RVO or (Return Value Optimization)
    SpreadsheetCell(const SpreadsheetCell &src);

    void setValue(double value);

    double getValue() const;

    void setString(std::string_view str);

    std::string getString() const;

    // Assignment operator
    SpreadsheetCell &operator=(const SpreadsheetCell &rhs);

private:
    std::string doubleToString(double d) const;

    double stringToDouble(std::string_view s) const;

    double m_value{0};
};