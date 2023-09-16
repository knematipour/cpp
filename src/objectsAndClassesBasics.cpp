#include <iostream>
#include <string>
#include <string_view>
#include <charconv>
#include <memory>
#include <typeinfo>

class SpreadsheetCell
{
public:
    // changed for providing multiple constructors
    // defauld constructor is provided ONLY when no constructor is defined!
    // The problem called Most Vexing Parse
    SpreadsheetCell() = default; // adds a compiler-generated default constructor to the class
    // convetor constructor, can be marked explicit
    SpreadsheetCell(double initialValue);
    SpreadsheetCell(std::string_view initialValue);

    // copy constructor is called when object is passed by value to a function
    // Also called when object is returned by value from a funciton
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

// implementation of assignment operator
SpreadsheetCell &SpreadsheetCell::operator=(const SpreadsheetCell &rhs)
{
    // to prevent copy unto itself
    if (this == &rhs)
    {
        return *this;
    }

    // always return *this
    m_value = rhs.m_value;
    return *this;
}

// copy constructor has access to the private data of the source object
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell &src) : m_value{src.m_value}
{
    std::cout << "copy constructor is called!\n";
}

SpreadsheetCell::SpreadsheetCell(double d) : m_value{d}
{
}

SpreadsheetCell::SpreadsheetCell(std::string_view s)
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

void SpreadsheetCell::setString(std::string_view str)
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

double SpreadsheetCell::stringToDouble(std::string_view str) const
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

    // copy constructor is called!
    SpreadsheetCell c3{c1};
    // does not call copoy constructor! Object exists already. Calls the assignment operator
    c2 = c1;

    // take a good look later on.
    using namespace std::literals;

    SpreadsheetCell c4{4};
    // use os converting constructors
    // can be stopped by using explicit before the constuctor
    c4 = 10;
    c4 = "4.12"sv;
    std::cout << "The final value for c4 is : " << c4.getString() << "\n";

    std::string s1;
    // this creates a temp string by calling the copy constructor of string and then assignmnet operator of s1
    s1 = c4.getString(); 
    // this is where very important "COPY ELISION" by compiler kicks in 
    // this line calls the copy constructor for the temp opbject and the copy constructor for s2 
    std::string s2 = c4.getString();


}