#include <iostream>
#include "testIterators.h"
#include <iterator>
#include <vector>

// C++ uses iterator pattern to access elements of a container
// every container has its own specific iterator, which is basically a glorified pointer to a specific element in container
// there are 6 categories of iterators:
//      Input, Output, Forward, Bidirectional, Random Access, Contiguous

// all containers support following iterators:
// being: iterator pointing to the beginning of the container
// end: iterator to one past the last element of the container
// cbeing and : constant version of begin and end
// rbeing: reverse version of begin and end
// crbegin and crend: constant versions of rbeing and rend
// <iterator> supports the respective functions for the above iterators
// using std::begin is recommended to benefit from ADL
// std::distance() calculates the distance between two iterators in a container
// iterator_traits have 5 aliases:
// value_type, difference_type, iterator_category, pointer, reference

template<typename IteratorType>
void testIteratorTrait(IteratorType it) {
    // define a variable of the type that the iterator points to
    // notice typename. Necessary when accessing type of value.
    typename std::iterator_traits<IteratorType>::value_type temp;
    temp = *it;
    std::cout << temp << std::endl;

}

template<typename Iter>
void myPrint(Iter begin, Iter end) {
    for (auto iter{begin}; iter != end; iter++) {
        std::cout << *iter << " ";
    }
}

// returns an iterator to the value element
template<typename Iter>
auto myFind(Iter begin, Iter end, const typename std::iterator_traits<Iter>::value_type &value) {
    for (auto e{begin}; e != end; e++) {
        if (*e == value) {
            return e;
        }
    }

    return end;
}

void testIterators() {
    std::cout << "Testing iterators\n" << std::endl;
    std::vector v{5};
    testIteratorTrait(v.cbegin());

    // easy sample one
    std::vector s1{1, 2, 3, 4, 5, 6, 7, 8};
    for (auto it = s1.cbegin(); it != s1.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    myPrint(std::cbegin(s1), std::cend(s1));
    std::cout << "\n";

    std::vector<int>::const_iterator iter1{myFind(std::cbegin(s1), std::cend(s1), 5)};
    if (iter1 != std::cend(s1)) {
        std::cout << "iter: " << *iter1 << std::endl;

    }

    // stream iterators

}