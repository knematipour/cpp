#include "Spreadsheet.hpp"
#include <iostream>

// move semantics

// lvalue is anything of which we can an address (named variable, etc)
// rvalue is anything that is not a lvalue (literal, temp object or value)
// rvalue reference is a reference to a rvalue (temporary object or an object that is moved from with std::move)
// the purpose of an rvalue reference is to allow certain overloaded functions to be called when an
//      rvalue is involved

class MyClass {
public:
    MyClass(int i) : i{i} { std::cout << "ctor" << std::endl; }

    ~MyClass() { std::cout << "dtor" << std::endl; }

    MyClass(MyClass &c) : i{c.i} { std::cout << "copy ctor" << std::endl; }

    MyClass &operator=(MyClass &c) {
        std::cout << "assignment operator" << std::endl;
        i = c.i;
        return *this;
    }

    MyClass(MyClass &&rhs) : i{rhs.i} {
        rhs.i = 0;
        std::cout << "move ctor" << std::endl;
    }

    MyClass &operator=(MyClass &&rhs) {
        std::cout << "move assignment" << std::endl;
        i = rhs.i;
        rhs.i = 0;
        return *this;
    }
//    MyClass &operator=(MyClass &&rhs) = default;

    int i;
};

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

MyClass myClassArgument(MyClass &c) {
    std::cout << "-------> myClassArgument" << std::endl;
    // MyClass c1{};
    return MyClass{10};
}

void testMyClass() {
    MyClass c1{20};
    MyClass c2{c1};
    MyClass c3{std::move(c1)};
    std::cout << "value or i for c3 is: " << c3.i << std::endl;
    MyClass c4{1};
    c4 = c1;
    c4 = std::move(c2);
    c1 = myClassArgument(c4);
    // this is a very interesting optimization.
    MyClass c5{myClassArgument(c1)};
    std::cout << "value or i received is: " << c5.i << std::endl;
}

void test_advanced_classes() {
    //test_rvalue_call();
    testMyClass();

}