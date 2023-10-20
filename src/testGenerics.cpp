#include <iostream>
#include "testGenerics.h"
#include "Grid.h"

void testGenerics() {
    std::cout << "Testing Generic programming!\n" << std::endl;
    Grid<int> ig1{5, 5};
    ig1.at(0,0) = 20;

    Grid ig2{ig1};
    auto b {ig2.returnSize()};
    std::cout << "height: " << b.first << " width: " << b.second << std::endl;

    ig2.at(1,1) = 10;
    std::cout << "the 1,1 coordinates are set to: " << ig2.at(1,1) << std::endl;
    std::cout << "the 0,0 coordinates are set to: " << ig2.at(0,0) << std::endl;

}