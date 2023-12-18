#include <iostream>
#include "testIterators.h"
#include <iterator>
#include <vector>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <ranges>


// C++ uses iterator pattern to access elements of a container
// every container has its own specific iterator, which is basically a glorified pointer to a specific element in container
// there are 6 categories of iterators:
//      Input, Output, Forward, Bidirectional, Random Access, Contiguous

// all containers support following iterators:
// begin: iterator pointing to the beginning of the container
// end: iterator to one past the last element of the container
// cbegin and : constant version of begin and end
// rbegin: reverse version of begin and end
// crbegin and crend: constant versions of rbegin and rend
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

template<typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target) {
    for (auto iter{begin}; iter != end; ++iter, ++target) { *target = *iter; }
}

template<typename InputIter>
auto mySum(InputIter begin, InputIter end) {
    auto sum{*begin};
    for (auto element{++begin}; element != end; ++element) { sum += *element; }
    return sum;
}

void printMessage(const std::string &message, auto &range) {
    std::cout << message;
    for (auto e: range) {
        std::cout << " " << e;
    }
    std::cout << "\n";
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
    std::vector values{1, 2, 3, 4, 5};
    std::vector<int> copyValues(values.size());
    // top copy a range to another range
    myCopy(std::cbegin(values), std::cend(values), std::begin(copyValues));
    // std::ostream_iterator<int> {std::cout, " "} is an iterator to tbe begining of std::cout stream and " " is the delimiter
    myCopy(std::cbegin(values), std::cend(values), std::ostream_iterator<int>{std::cout, " "});
    std::cout << "\n";
    myCopy(std::cbegin(copyValues), std::cend(copyValues), std::ostream_iterator<int>{std::cout, " "});
    std::cout << "\n";

    int sumValues{mySum(std::cbegin(values), std::cend(values))};
    std::cout << "Sum: " << sumValues << std::endl;
    // std::istream_iterator<int> inputIter{std::cin};
    // std::istream_iterator<int> endIter;
    // int result{mySum(inputIter, endIter)};
    // std::cout << "New Sum: " << result << std::endl;

    // there are 5 iterator adapters, namely
    // back_insert_iterator, front_insert_iterator, insert_iterator, reverse_iterator, move_iterator

    // 1) basic insert iterator: insert(position, element)
    // 2) back insert iterator: push_back(element)
    // 3) front insert iterator: push_front(element)

    // sample for back_insert
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2; // the difference is here. We don't need to assign the size since new elements are inserted
    std::vector<int> v3;

    std::back_insert_iterator<std::vector<int>> inserter{v2};
    myCopy(std::cbegin(v1), std::cend(v1), inserter);

    // using std::back_inserter creates a back_insert_iterator to the given range
    myCopy(std::cbegin(v1), std::cend(v1), std::back_inserter(v3));
    std::set<int> set1;
    std::insert_iterator<std::set<int>> s_inserter{set1, set1.begin()};
    myCopy(v1.cbegin(), v1.cend(), s_inserter);
    // using rbegin and rend iterators, when you apply ++ to the iterator, it goes back
    myCopy(set1.rbegin(), set1.rend(), std::ostream_iterator<int>{std::cout, " "});

    // move_iterator moves from the elements

    std::cout << std::endl;


    // A range is a "concept" which means it defines the requirements of a type that allows iteration over its elements
    // Any data structure that supports begin() and end() is a range!
    std::vector<int> v4{12, 1, 33, 46, 74, 3, 36};
    std::sort(v4.begin(), v4.end()); // simple sort algorithm
    myCopy(v4.cbegin(), v4.cend(), std::ostream_iterator<int>{std::cout, " "});
    std::ranges::sort(v4);
    std::ranges::copy(v4, std::ostream_iterator<int>(std::cout, " "));

    // projection is an algorithm applied to the element before they are handed to the algorithm
    // std::ranges::sort(container, initial value, [](const type& T){return something;};

    // Views also perform operation on underlying elements. they can be pipelined
    // a view can be created using "Range Adapters"
    // std::ranges::operation_view{range, arguments} can also be done as:
    // range | std::ranges::operation_view (arguments)

    std::cout << std::endl;

    std::vector v5{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printMessage("Original range: ", v5);

    auto result1{v5
                 | std::views::filter([](const auto &element) { return element % 2 == 0; })};
    printMessage("Odd elements: ", result1);

    auto result2{v5
                 | std::views::transform([](auto &value) { return value * 2.0; })
                 | std::views::drop(5)
                 | std::views::reverse
    };
    printMessage("Double elements: ", result2);

    // for (auto &val: result2) { val += 2; } does not compile and I don't know why!
    // printMessage("Original Values: ", v5);

    // Create an infinite sequence of the numbers 10, 11, 12, ...
    auto v6{std::views::iota(10)};
    // Filter out all odd values, leaving only the even values.
    auto result11{v6
                  | std::views::filter([](const auto &value) { return value % 2 == 0; })};
    // Transform all values to their double value.
    auto result22{result11
                  | std::views::transform([](const auto &value) { return value * 2.0; })};
    // Take only the first ten elements.
    auto result33{result22 | std::views::take(10)};
    printMessage("Result: ", result33);
}