#include <iostream>
#include "testGenerics.h"
#include "Grid.h"
#include <cassert>

void testGenerics() {
    std::cout << "Testing Generic programming!\n" << std::endl;
    Grid<int> ig1{5, 5};
    ig1.at(0, 0) = 20;

    Grid ig2{ig1};
    auto b{ig2.returnSize()};
    std::cout << "height: " << b.first << " width: " << b.second << std::endl;

    ig2.at(1, 1) = 10;
    std::cout << "the 1,1 coordinates are set to: " << ig2.at(1, 1).value() << std::endl;
    std::cout << "the 0,0 coordinates are set to: " << ig2.at(0, 0).value() << std::endl;

    int i{ig1.at(0, 0).value_or(0)};
    std::cout << "i: " << i << std::endl;
    int j{ig1.at(2, 2).value_or(0)};
    std::cout << "j: " << j << std::endl;

    ig2 = ig1;

    OtherGrid<int, 5, 5> ogrid1;
    ogrid1.at(0, 0) = 30;
    std::cout << "O,0 is assigned: " << ogrid1.at(0, 0).value_or(0) << std::endl;
    std::cout << "and the size of orgrid1 is: " << ogrid1.returnSize().first << " by " << ogrid1.returnSize().second
              << std::endl;
    OtherGrid<int, 5, 5> ogrid2;
    ogrid2 = ogrid1;

    // ogrid1 and ogrid2 should be of the same size for assignment or copy to work. Otherwise, they will not be of the
    // same type.

    std::clog << "Testing CLOG!\n";

}