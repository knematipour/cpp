#include <iostream>

void test_basic()
{
    // Automatic variable. deleted when the program leaves the scope.
    int i{7};

    // creating an integer in free-store memory (Heap)
    int *pi = new int;
    int *pi1{new int};
    int *pi2{new (std::nothrow) int}; // if the allocation fails, return nullptr
    if (pi2 != nullptr)
    {
        std::cout << "memory allocated successfully!\n";
    }

    // releasing the memory from the heap
    delete pi;
    delete pi1;
    pi = nullptr; // we can set the pointer to nullptr after the memory is released.
    pi1 = nullptr;
}

class Simple
{
public:
    Simple() { std::cout << "Object of class simple being constructed\n"; };
    ~Simple() { std::cout << "Object of class simple being destructed\n"; };
};

void test_arrays()
{
    // test bascic-type arrays
    int myIntArray[]{1, 2, 3, 4, 5};

    // basic-type array on the heap
    int *otherIntArray{new (std::nothrow) int[5]};
    // this line only works with c++ 20
    // int *anotherIntArray {new int[]{1, 2, 3, 4, 5}};
    // it works like this
    int *anotherIntArray{new int[5]{1, 2, 3, 4, 5}};

    // deleting the non-automatic array
    delete[] otherIntArray;
    otherIntArray = nullptr;

    delete[] anotherIntArray;
    anotherIntArray = nullptr;

    // Simple object instantiation
    Simple s;
    // automatic array
    Simple myObjectArray[3];

    Simple *oArray { new Simple[3]};
    delete[] oArray;
    oArray = nullptr;
}

void test_memory_management()
{
    test_basic();
    test_arrays();
}