#include <iostream>
#include <string>
#include <string_view>
#include <charconv>
#include <memory>

class SpreadsheetCell
{
public:
    // changed for providing multiple constructors
    // defauld constructor is provided ONLY when no constructor is defined!
    // The problem called Most Vexing Parse
    SpreadsheetCell() = default; // adds a compiler-generated default constructor to the class 
    SpreadsheetCell(double initialValue);
    SpreadsheetCell(std::string initialValue);
    void setValue(double value);
    double getValue() const;

    void setString(std::string str);
    std::string getString() const;

private:
    std::string doubleToString(double d) const;
    double stringToDouble(std::string s) const;
    double m_value{0};
};

SpreadsheetCell::SpreadsheetCell(double d)
{
    setValue(d);
}

SpreadsheetCell::SpreadsheetCell(std::string s)
{
    setString(s);
}

void SpreadsheetCell::setValue(double value)
{
    m_value = value;
}

double SpreadsheetCell::getValue() const
{
    return m_value;
}

void SpreadsheetCell::setString(std::string str)
{
    m_value = stringToDouble(str);
}

std::string SpreadsheetCell::getString() const
{
    return doubleToString(m_value);
}

std::string SpreadsheetCell::doubleToString(double d) const
{
    return std::to_string(m_value);
}

double SpreadsheetCell::stringToDouble(std::string str) const
{
    double number{0};
    std::from_chars(str.data(), str.data() + str.size(), number);
    return number;
}

void test_classes_basics()
{
    // creating objects on the stack
    SpreadsheetCell c1{0}, c2{0};
    c1.setValue(5);
    c2.setString("3.2");
    std::cout << "The value to c1 is set to: " << c1.getString() << "\n";
    std::cout << "The value to c2 is set to: " << c2.getString() << "\n";

    // creating objects on the heap
    SpreadsheetCell *p1{new SpreadsheetCell{0}};
    std::unique_ptr<SpreadsheetCell> p2{std::make_unique<SpreadsheetCell>(0)};
    auto p3{std::make_shared<SpreadsheetCell>(0)};

    p1->setValue(10);
    p2->setString("3.14");
    p3->setValue(30);

    std::cout << "p1: " << p1->getString() << " p2: " << p2->getString() << " p3: " << p3->getString() << "\n";
    delete p1;
    p1 = nullptr;
}