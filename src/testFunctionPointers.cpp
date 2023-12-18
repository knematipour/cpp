#include "testFunctionPointers.h"
#include <iostream>
#include <span>
#include <vector>
#include <functional>
#include <queue>
#include <ranges>
#include <memory>


// A callback i something that can be called, such as function pointer or something that behaves like a function such as
// an object that the () operator has been overloaded or an inline lambda expression

// a class that overloads () operator is called a function object or a "functor"

// A function that accepts other functions is called a "Higher-Order" function

using Matcher = bool (*)(int, int);
// alternatively can be written as follows:
using Matcher1 = std::function<bool(int, int)>;

using MatchHandler = void (*)(size_t, int, int);
// alternatively can be written as:
using MatchHandler1 = std::function<void(size_t, int, int)>;

bool intEqual(int first, int second) { return first == second; }

void intHandler(size_t pos, int first, int second) {
    std::cout << "A match of vlues found at position: " << pos << std::endl;
}

void
findMatches(std::span<const int> values1, std::span<const int> values2, Matcher matcher, MatchHandler matchHandler) {
    if (values1.size() != values2.size())
        return;

    for (size_t i = 0; i < values1.size(); ++i) {
        if (matcher(values1[i], values2[i])) {
            matchHandler(i, values1[i], values2[i]);
        }
    }
}

void testFuncionPointer() {
    std::vector v1{1, 2, 3, 4, 5, 6, 7};
    std::vector v2{1, 0, 3, 0, 0, 0, 7};
    findMatches(v1, v2, intEqual, intHandler);
}

int multiply(int a, int b) { return a * b; }

void testFunctional() {
    std::function<int(int, int)> multi{multiply};
    std::function f1{multiply};
    std::cout << "test: " << multi(2, 3) << std::endl;

}

// testing function objects
class IsLargerThan {
public:
    explicit IsLargerThan(int value) : m_value{value} {}

    bool operator()(int value1, int value2) {
        return value1 > m_value && value2 > m_value;
    }

private:
    int m_value;
};

// find the error here!!!
void testFunctionObjects() {
    std::vector values1{2, 500, 6, 9, 10, 101, 1};
    std::vector values2{4, 4, 2, 9, 0, 300, 1};
    // findMatches(values1, values2, IsLargerThan { 100 }, intHandler);
}

void testPredefinedFunctors() {
    // arithmetic functors

    std::plus<int> myPlus;
    int p{myPlus(10, 12)};

    std::priority_queue<int, std::vector<int>, std::greater<>> myQueue;
    myQueue.push(3);
    myQueue.push(1);
    myQueue.push(4);
    myQueue.push(2);
    //std::ranges::copy(myQueue, std::ostream_iterator<int>(std::cout," "));
    while (!myQueue.empty()) {
        std::cout << myQueue.top() << std::endl;
        myQueue.pop();
    }
}

void testLambda() {
    // lambda expressions are anonymous inline functions
    auto basicLambda{[] {
        std::cout << "my basic lambda!" << std::endl;
    }};
    basicLambda();

    // lambda with input and a return type
    auto doubleLambda{[](int i) -> int { return i * 2; }};
    std::cout << "Double 3 is: " << doubleLambda(3) << std::endl;

    // above lambda expressions are called "stateless" since they don't capture environment variables
    float f{3.14159265458979323846264338f};
    // captured values by value are const by default, unless you define the lambda as mutable like this
    auto captureLambda{[f]mutable { f = f * 2; }};

    auto var{1};
    auto lambdaChange{[&var]() { var = var + 2; }};
    lambdaChange();
    std::cout << "Value doubled! " << var << std::endl;


}

void testFunctionPointers() {
    std::cout << "testing function pointer and lambda expressions!" << std::endl;
    testFuncionPointer();
    testFunctional();
    testFunctionObjects();
    testPredefinedFunctors();
    testLambda();
}