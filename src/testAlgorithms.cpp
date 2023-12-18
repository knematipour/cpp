#include "testAlgorithms.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

// STL algorithms: find, sort and process elements in a container
// independent of the type of underlying element as well as the type of container
// the "magic" is that they work on iterators and not the container itself

void testFind() {
    // finds looks for a specific element in a range
    // returns an iterator to the element if finds it or end iterator if it does not.

    std::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto iter{std::find(std::cbegin(vec1), std::cend(vec1), 8)};
    if (iter != std::cend(vec1)) {
        std::cout << "element found! " << *iter << std::endl;
        std::cout << "Index: " << std::distance(std::cbegin(vec1), iter) << std::endl;
    }

    // does the same thing but fancier
    if (auto it{std::find(std::cbegin(vec1), std::cend(vec1), 5)}; it != std::cend(vec1)) {
        std::cout << "Index of the item is: " << std::distance(std::cbegin(vec1), it) << std::endl;
    }

    if (auto it2{std::find_if(std::cbegin(vec1), std::cend(vec1), [](int e) { return e > 5; })}; it2 !=
                                                                                                 std::cend(vec1)) {
        std::cout << "the first index: " << std::distance(std::cbegin(vec1), it2) << std::endl;
    }

}

// NON modifying sequential algorithms

// Search algorithms: find, find_if, find_if_not, adjacent_find, find_first_of

void testSequential() {
    std::string str1{"Hello World!"};
    if (auto iter{std::find(std::cbegin(str1), std::cend(str1), '!')}; iter != str1.cend()) {
        std::cout << "Index of !: " << std::distance(std::cbegin(str1), iter) << std::endl;
    }

    std::string str2{"jk"};
    if (auto iter{std::find_first_of(std::cbegin(str1), std::cend(str1), str2.cbegin(), str2.cend())}; iter !=
                                                                                                       str1.cend()) {
        std::cout << "Index of jk: " << std::distance(std::cbegin(str1), iter) << std::endl;
    } else {
        std::cout << "jk NOT found!" << std::endl;

    }

    std::string str3{"lo"};
    auto pos{str1.find(str3)};
    if (pos != std::string::npos) {
        std::cout << "Found at: " << pos << std::endl;
    }
}

// Counting algorithms: all_of, any_of, non_of
void testCounting() {
    std::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
    if (std::all_of(std::cbegin(vec1), std::cend(vec1), [](int i) { return i > 0; })) {
        std::cout << "All members of the vec are positive numbers!" << std::endl;
    }
}


// Modifying sequence algorithms
void testGenerate() {
    std::vector<int> values(10); // Create a vector of 10 elements.
    int value{1};
    generate(begin(values), end(values), [&value] {
        value *= 2;
        return value;
    });
    for (const auto &i: values) { std::cout << i << " "; }
}

void testTransform() {
    // applies a callback to all the elements in a SOURCE range and stores the results back in a DESTINATION range
    std::vector<int> vec1{2, 4, 6, 8};
    std::transform(std::begin(vec1), std::end(vec1), std::begin(vec1), [](int i) { return i * 2; });
    std::cout << "\nOUTPUT: ";
    std::ranges::copy(vec1, std::ostream_iterator<int>(std::cout, " "));
}

void testAlgorithms() {
    std::cout << "Testing STL Algorithms ... ! " << std::endl;
    testFind();
    testSequential();
    testCounting();
    testGenerate();
    testTransform();
}