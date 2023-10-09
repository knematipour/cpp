#include "Spreadsheet.hpp"
#include <iostream>

// move semantics

// lvalue is anything of which we can an address (named variable, etc)
// rvalue is anything that is not a lvalue (literal, temp object or value)
// rvalue reference is a reference to a rvalue (temporary object or an object that is moved from with std::move)
// the purpose of an rvalue reference is to allow certain overloaded functions to be called when an
//      rvalue is involved

void handleMessage(std::string &message) {
    std::cout << "Message handled from lvalue function: " << message << std::endl;
}

void handleMessage(std::string &&message) {
    std::cout << "Message handled from rvalue function: " << message << std::endl;
}

void test_rvalue_call() {
    std::string str{"Hello"};
    handleMessage(str);
    // a temp object is constructed with a converting ctor and then passed to the function, triggers rvalue overload
    handleMessage("Ho ho ho!");
    // why does this call not empty the str?
    handleMessage(std::move(str));
    std::cout << std::boolalpha << str.empty() << std::endl;
    std::string str1{std::move(str)};
    std::cout << std::boolalpha << str.empty() << std::endl;
}


void test_advanced_classes() {
    std::cout << "Testing advanced classes\n";
    test_rvalue_call();
    // Spreadsheet sheet1{};
}