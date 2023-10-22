#include <iostream>
#include <limits>
#include <array>
#include <vector>
#include <optional>
#include <initializer_list>

void test_data_types() {
    int i{0};
    short s{0};
    long l{-7L};
    long long ll{14LL};
    float f{3.1415f};
    double d{3.141592};
    long double ld{3.1415926535897932384626};
    char c{'c'};
    bool b{true};

    std::cout << "The maximum value for an integer is: " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "The minimum value for an integer is: " << std::numeric_limits<int>::min() << std::endl;

    std::cout << "The maximum value for an float is: " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "The minimum value for an float is: " << std::numeric_limits<float>::min() << std::endl;
}

enum class PieceTypes : unsigned long {
    King = 1,
    Queen,
    Rook,
    Pawn
};

enum class altitude : char {
    high = 'h',
    low = 'l', // trailing comma only allowed after CWG 518
};

// We can use the lines below if the compiler supports C++ 20
// using enum PieceTypes;
// PieceType p{King};
void test_enum_class() {
    PieceTypes piece{PieceTypes::King};
    altitude alt = static_cast<altitude>('l');

    if (alt == altitude::low) {
        std::cout << "Low Detected\n";
    }
}

// c++ function attribute sample
[[nodiscard]] int func() {
    return 42;
}

void test_array() {
    // C-style array
    int myArray[10];
    myArray[0] = 1;

    // modern array
    std::array<int, 5> arr{1, 2, 3, 4, 5};
    std::cout << "The size of this array: " << arr.size() << "\n";
    std::cout << "The first element this array: " << arr[0] << "\n";
}

void test_vector() {
    // easiest way to use a vector
    std::vector<int> iVector{1, 2, 3, 4};
    iVector.push_back(5);
    iVector.push_back(6);

    for (auto e: iVector) {
        std::cout << e << "\t";
    }
    std::cout << "\n";
}

void test_pair() {
    std::pair<double, int> myPair{1.23, 10};
    std::cout << "First element: " << myPair.first << " second element is: " << myPair.second << "\n";
}

std::optional<int> test_optional(bool b) {
    if (b) {
        return 42;
    }
    return std::nullopt;
}

void test_optional_argument(std::optional<int> arg) {
    if (arg.has_value()) {
        std::cout << "The passed value is: " << arg.value() << "\n";
    } else {
        std::cout << "No Value is passed!\n";
    }
}

void test_structured_binding() {
    std::array values{1, 2, 3};

    auto [x, y, z]{values};
    std::cout << "value of the x is : " << x << "\n";
}

void test_range_based_loops() {
    for (std::array arr{1, 2, 3, 4, 5, 6}; auto e : arr)
    {
        std::cout << e << "\t";
    }
    std::cout << "\n";
}

int test_initializer_list(std::initializer_list<int> args) {
    int total{0};

    for (auto e: args) {
        total += e;
    }
    return total;
}

// sample for uniform initializers
class UniFormInit {
public:
    UniFormInit(int x, int y) : x_{x}, y_{y} {
    }

private:
    int x_, y_;
};

void test_const(const std::string *param) // parameter cannot changed in the function
{
    // first use of const, to make a variable unchangeable.
    const double pi{3.141592653589793238462643383279};

    // const and pointers
    const int *ip;
    ip = new int[10];
    // ip[4]=5;  does not compile

    int const *cp;
    cp = new int[10];
    // cp[4] = 5;   same as the one above. does not compile

    // int* const bp; does not compile this way because it cannot be initialized afterwards
    int *const bp{new int[10]};
    bp[4] = 5; // works but bp cannot point to another memory
}

class SomeClass {
public:
    SomeClass(int m) : member_{m} {};

    // second use of const here for methods who don't change the value of the class members
    int return_member() const { return member_; };

private:
    int member_;
};

std::string hello_world() {
    return "Hello World!\n";
}

// reference class members cannot be initialized in constructor body but this is OK. 
class MyClass {
    MyClass(int m) : m_{m} {}

    int &m_;
};

void test_references() {
    // easiet form of reference use.
    int x{3};
    int &xRef{x};

    xRef = 10;
    std::cout << "the new value of x is: " << x << "\n";

    // std::string& sRef{hello_world()}; does not compile since it lacks const!
    const std::string &sRef{hello_world()};
    const int &iRef{5}; // compiles since it is a const ref

    std::pair p{"Hello", 5};
    // both work fine! one is reference to non-const and the other is reference to const! 
    auto &[p1, p2] {p};
    const auto &[p3, p4] {p};
    // p4 = 10; does not compile  
}

void crash_course() {
    test_data_types();
    test_enum_class();
    func(); // generates compile time warning if the return type is not checked!
    test_array();
    test_vector();
    test_pair();
    std::optional<int> data1{test_optional(true)};
    if (data1.has_value()) {
        std::cout << "the value of the optional is for true is: " << data1.value() << "\n";
    }
    std::optional<int> data2{test_optional(false)};
    if (!data2.has_value()) {
        // this line throws a std::bad_optional_access exception!
        // std::cout << "the value of the optinal is for false is: " << data2.value() << "\n";

        std::cout << "the value of the optinal is for false is: " << data2.value_or(0) << "\n";
    }

    test_optional_argument(10);
    test_optional_argument(std::nullopt); // argument cannot be empty and std::nullopt shall be passed!

    test_structured_binding();
    test_range_based_loops();

    int sum{test_initializer_list({1, 2, 3, 4})};
    std::cout << "the sum is: " << sum << "\n";

    test_references();
}