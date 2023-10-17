#include <iostream>
#include <vector>
#include <iomanip>
#include <charconv>
#include <chrono>

// important points to remember
// if the virtual keyword is not used, the derived class is going to hide the base method, not override it
// all methods in C++ are non-virtual by default but in Java it is the other way around
// using the override keyword helps to catch changes in the base class (compile error is there is a change)
// vtable is created for method that are virtual. Small performance penalty
// final prevents the class to be inherited from
// final prevents the method from being overridden
// if the class is not final, the destructor should always be virtual
// if destructor is implemented the rule of 5 kicks in
// rule of zero is better than rule of 5


// the order of constructor in inherited classes
// 1. the Ctor of the Base Class
// 2. non-static members are initialized
// 3. the body of the constructor is executed

// the order of the destructors is reverse
// 1. the body of the destructor is called
// 2. members of the class are destructed
// 3. parent destructor is called
class BaseClass {
public:
    BaseClass() {
        std::cout << "BaseClass ctor!" << std::endl;
    }

    BaseClass(BaseClass &src) {
        std::cout << "copy ctor" << std::endl;

    }

    BaseClass(int i) : m_privateInt{} {
        std::cout << "non-default ctor of BaseClass!" << std::endl;
    };

    void someMethod() {
        std::cout << "None virtual Some Method!" << std::endl;
    };

    virtual void methodToOverride() {
        std::cout << "virtual method to override in BaseClass" << std::endl;

    }

protected:
    int m_protectedInt{0};

private:
    int m_privateInt{0};

};

class DerivedClass : public BaseClass {
public:
    DerivedClass() = default;

    // DerivedClass(int i) : m_protectedInt{i} { cannot initialize protected members of parent in intilizer list

    //}
    DerivedClass(int i) : BaseClass{10} {
        m_protectedInt = 20;
    }


    void someOtherMethod() {
        std::cout << "some other method can access pm_protectedInt from base!" << std::endl;
        std::cout << "the value of m_protectedInt is: " << m_protectedInt << std::endl;

    };

    void methodToOverride() override {
        std::cout << "method to override on DerivedClass" << std::endl;
    }
};

void testClamp() {
    std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
    for (const int v: {-129, -128, -1, 0, 42, 127, 128, 255, 256}) {
        std::cout
                << std::setw(04) << v
                << std::setw(20) << std::clamp(v, INT8_MIN, INT8_MAX)
                << std::setw(21) << std::clamp(v, 0, UINT8_MAX) << '\n';
    }
}

void testiStringStream() {
    std::istringstream is("12 34 56");
    int n{0};
    is >> n;
    std::cout << "n is: " << n << std::endl;
    is >> n;
    std::cout << "n is: " << n << std::endl;
    std::string s{};
    is >> s;
    std::cout << "s is: " << s << std::endl;

    std::string str{"Hello,, World!"};
    std::istringstream is1{str};
    std::string st1;
    is1 >> std::setw(2) >> st1;
    std::cout << "st1: " << st1 << "/" << std::endl;
    is1 >> std::setw(6) >> st1;
    std::cout << "st1: " << st1 << "/" << std::endl;

}

void testSetW() {
    std::cout << "no setw: [" << 423456 << "]\n"
              << "setw(6): [" << std::setw(6) << 42 << "]\n"
              << "no setw, several elements: [" << 89 << 12 << 34 << "]\n"
              << "setw(6), several elements: [" << 89 << std::setw(6) << 12 << 34 << "]\n";
}

void testCasting() {
    std::cout << "TESTING CASTING!" << std::endl;

    DerivedClass obj1{};
    // this is slicing
    BaseClass obj2{obj1};

    // this is NOT slicing
    // this is UP casting
    BaseClass &obj3{obj1};
    BaseClass *pobj1{&obj2};

    // is the method or a function takes a reference as an argument, they can receive the parameter without slicing

    // DOWN casting is most likely a sign of bad design
    DerivedClass *pobj2{static_cast<DerivedClass *>(pobj1)};

    // cast successful, actual object is derived!
    DerivedClass *pobj3{dynamic_cast<DerivedClass *>(pobj2)};
    if (pobj3 != nullptr) {
        std::cout << "Cast was successful!" << std::endl;

    } else {
        std::cout << "Cast Failed!" << std::endl;

    }
}


void testChrono() {
    auto today = std::chrono::system_clock::now();
    // std::cout << "Today is: " << today << std::endl; not implemented yet before gcc 14

    auto today_t = std::chrono::system_clock::to_time_t(today);
    std::cout << "The current time is: " << std::ctime(&today_t) << std::endl;


}

void test_inheritance() {
    std::cout << "test inheritance capabilities\n";
    DerivedClass dobj1;
    dobj1.someOtherMethod();
    dobj1.someMethod();

    BaseClass &bobj1{dobj1};
    bobj1.methodToOverride();

    // calls the copy constructor of the base class. if there is none, calls the normal constructor
    BaseClass bobj2{dobj1};
    bobj2.methodToOverride();

    DerivedClass dobj3{20};

    // testClamp();
    // testSetW();
    // testiStringStream();
    // testCasting();

    std::string str1{"3.14"};
    std::istringstream is{str1};
    double d;
    is >> d;
    std::cout << "value of d: " << d << std::endl;

    std::string str2{"4.12"};
    std::from_chars(str2.data(), str2.data() + str2.size(), d);
    std::cout << "value of d: " << d << std::endl;


    testChrono();
}