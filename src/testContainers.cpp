#include "testContainers.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <memory>
#include <limits>
#include <list>
#include <forward_list>
#include <map>
#include <set>

// there are 4 types of containers:
// 1) sequential
//      vector, deque, list, forward_list, array
// 2) Associative
// 3) Unordered associative (hash table)
// 4) Container adapters

// containers use value semantics (copy, assign destruct)

// classes that are going to be stored in STL containers shall be "copyable" and when an element is requested a
// reference to that copy is returned!

// we can use containers to store move-only types (such as unique_ptr) but some actions may not compile then

// all containers have an "allocator" parameter but it is defaulted std::allocator<T>

// some containers accept Comparators (such as map) which is used to order elements std::less<T>

// default requirements: ctor, copy ctor, assignment, move assignment, destructor, default ctor, operator==, operator<

// ordered associative containers:
// does not store elements in a linear configuration, instead they use a mapping of Keys and Values
// 1) map
// 2) Mulimap
// 3) set
// Multiset
// they store elements in a sorted, tree-like structure
// they have unordered versions: unordered_map, unordered_set, ...


void testVector() {
    // std::vector; the elements are stored in contiguous memory (like other sequential containers)
    // inserting and deleting take linear time, they run in "amortized constant time". Random access has constant complexity
    // starting C++, the vector is constexpr

    std::vector<double> vec;
    double max{-std::numeric_limits<double>::infinity()};
    for (int i = 0; i < 3; ++i) {
        double d;
        std::cout << "Enter a Number: ";
        std::cin >> d; // also can use vec[i] directly
        vec.push_back(d);
        max = (d > max ? d : max);
    }

    auto result_view{vec | std::views::transform([max](auto &e) { return (e / max) * 100; })};
    std::ranges::copy(result_view, std::ostream_iterator<double>(std::cout, " "));

    std::vector<int> vec2(10, 100); // default size and default value for all the elements

    // vectors shall be passed by reference to const/non-const instead of by value to avoid the deep copy

    // use of assign method
    vec2.assign(5, 20);
    std::cout << std::endl;
    std::ranges::copy(vec2, std::ostream_iterator<int>(std::cout, " "));

    // remember iterators
    for (std::vector<int>::iterator iter{std::begin(vec2)}; iter != std::end(vec2); ++iter) {
        // do nothing
    }

    // use of std::ref
    std::string s1{"Hello!"};
    std::string s2{"World."};
    std::vector<std::reference_wrapper<std::string>> ref_vec{std::ref(s1), std::ref(s2)};
    ref_vec[0].get().append("!!");

    // test insert and erase
    std::vector<int> v1(10, 5);
    std::vector<int> v2;

    v2.insert(std::begin(v2), 3);
    for (int i = 0; i < 5; ++i) {
        v2.push_back(i);
    }
    std::cout << "\n";
    v2.insert(std::begin(v2) + v2.size(), std::begin(v1), std::begin(v1) + 3);
    std::ranges::copy(v2, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::ranges::copy(s1, std::ostream_iterator<char>(std::cout, "\\"));

    // example of emplace_back
    // emplace_back forwards the parameters given to it to the constructor of the type that is provided
    std::vector<std::string> vs1;
    vs1.emplace_back(5, 'a'); // returns a reference to the element that is inserted
    std::cout << "vs11[0]: " << vs1[0] << std::endl;

    // erase and insert in vector have linear complexity and invalidate all the iterators (naturally)

    // containers support move semantics (for examples to be returned from a function) but the type that is used should
    // mark its move constructor and move assignment as noexcept

}

void testDeque() {
    // stands for double ended queue
    // elements are NOT stored in contiguous memory. Similar to vector but less used
    // supports the following method:
    //      push_front()
    //      pop_front()
    //      emplace_front()
    //      does not invalidate iterators when insert or erase is called, hence not using contiguous memory
}


void testList() {
    // does not support random-access iterator
    std::list<std::string> l1{"one", "two"};
    std::list<std::string> l2{"three", "four"};
    l1.splice(++std::begin(l1), l2);
    std::ranges::copy(l1, std::ostream_iterator<std::string>(std::cout, " "));

    // forward_list sample
    // Create 3 forward lists using an initializer_list
    // to initialize their elements (uniform initialization).
    std::forward_list<int> list1{5, 6};
    std::forward_list list2{1, 2, 3, 4}; // CTAD is supported.
    std::forward_list list3{7, 8, 9};
    // Insert list2 at the front of list1 using splice.
    list1.splice_after(list1.before_begin(), list2);
    // Add number 0 at the beginning of the list1.
    list1.push_front(0);
    // Insert list3 at the end of list1.
    // For this, we first need an iterator to the last element.
    auto iter{list1.before_begin()};
    auto iterTemp{iter};
    while (++iterTemp != end(list1)) { ++iter; }
    list1.insert_after(iter, cbegin(list3), cend(list3));
    // Output the contents of list1.
    for (auto &i: list1) { std::cout << i << ' '; }
}

void testArray() {
    // same as vector but it is fixed size
}

void testContainerAdapters() {
    // there are three container adapters:
    // queue, priority_queue, stack
}

void testPair() {
    std::pair<std::string, int> p1{"hello", 1};
    std::cout << "First: " << p1.first << " and second: " << p1.second << std::endl;

}

void testMap() {
    // We use map when we want to access elements bases on Key/Value and they can be sorted
    // constructor takes:
    // 1) Key type, 2) Value type, 3) Comparison type, 4) Allocator
    std::map<std::string, int> m{
            {"hello",  1},
            {"world!", 2},
            {"Kaveh",  3},
            {"Seda",   4}
    };

    // maps require unique keys
    // insert functions a pair with first being an iterator and the second being a bool
    // map does NOT re-write the element if the key already exists

    auto ret{m.insert({"hello", 5})};
    if (ret.second) {
        std::cout << "Insert successful!" << std::endl;

    } else {
        std::cout << "Insert NOT successful!" << std::endl;
        // will execute since the key already exists
    }

    auto ret2{m.insert(std::make_pair("Jack", 2))};
    if (ret2.second) {
        std::cout << "Insert successful!" << std::endl;
        // runs!
    } else {
        std::cout << "Insert NOT successful!" << std::endl;
    }

    // since C++ 17
    if (auto ret3{m.insert({"John", 7})}; ret3.second) {
        std::cout << "John inserted successfully!" << std::endl;
    }

    // a sample of structured binding
    if (auto [iter, success]{m.insert(std::make_pair("Jones", 8))};success) {
        std::cout << "Jones inserted successfully!" << std::endl;
    }

    // insert_or_assign overwrites the element if already exists, takes two parameters

    // use of [] operator, this operator is not const!
    m["Mark"] = 9;

    // supports emplace(), emplace_hint() and try_emplace()

    for (auto iter{std::cbegin(m)}; iter != std::cend(m); ++iter) {
        std::cout << iter->first << " " << iter->second << std::endl;
    }

    // does the same as the one above using structured binding
    for (auto [key, value]: m) {
        std::cout << key << " " << value << std::endl;
    }

    auto it{m.find("Seda")};
    if (it != std::end(m)) {
        std::cout << "The Value for Seda is: " << it->second << std::endl;
        // runs, since Seda exists in the map
    }

    // how to remove an element
    it = m.find("Jack");
    if (it != std::end(m)) {
        m.erase(it);
    }

    // using node_handler
    auto extracted_node{m.extract("hello")};
    std::map<std::string, int> m2;
    m2.insert(std::move(extracted_node));
    m2.merge(m);

    // a multimap is a map that allows multiple values for the same key

}

// test set
void testSet() {
    // a series of values sorted without duplicates! 
    std::set<int> s1{22, 64, 12, 98, 10};
    // cool way of creating a vector from two iterators
    std::vector<int> v1{std::begin(s1), std::end(s1)};

    // iterating over a set
    for (const auto &e: s1) {
        std::cout << e << " " ;
        // set is stored in an ordered fashion
    }
    std::cout << std::endl;
    std::cout << "The element [10] exists in the set: " << s1.count(10);

}

void testContainers() {
    std::cout << "Testing Containers!" << std::endl;
    // testVector();
    // testList();
    // testPair();
    // testMap();
    testSet();
}