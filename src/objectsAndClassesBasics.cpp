#include "SpreadsheetCell.hpp"

#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <typeinfo>

// defining class to avoid compile error
class Foo;

class Bar {
public:
    void processFoo(Foo &foo);
};

// friend classes and method break encapsulation so they should be avoided
class Foo {
    friend class Bar; // declare a class as a friend 
    friend void Bar::processFoo(Foo &foo); // declare a method of a class as a friend
    friend void printFoo(Foo &foo); // declare a standalone function as a friend
};

void printFoo(Foo &foo) {

}

void test_classes_basics() {
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
    // does not call copy constructor! Object exists already. Calls the assignment operator
    c2 = c1;

    // take a good look later on.
    using namespace std::literals;

    SpreadsheetCell c4{4};
    // use os converting constructors
    // can be stopped by using explicit before the constructor
    c4 = 10;
    c4 = "4.12"sv;
    std::cout << "The final value for c4 is : " << c4.getString() << "\n";

    std::string s1;
    // this creates a temp string by calling the copy constructor of string and then assignment operator of s1
    s1 = c4.getString();
    // this is where very important "COPY ELISION" by compiler kicks in 
    // this line calls the copy constructor for the temp opbject and the copy constructor for s2 
    std::string s2 = c4.getString();

}