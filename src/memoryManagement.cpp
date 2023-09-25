#include <iostream>
#include <memory>

void test_basic() {
    // Automatic variable. deleted when the program leaves the scope.
    int i{7};

    // creating an integer in free-store memory (Heap)
    int *pi = new int;
    int *pi1{new int};
    int *pi2{new(std::nothrow) int}; // if the allocation fails, return nullptr
    if (pi2 != nullptr) {
        std::cout << "memory allocated successfully!\n";
    }

    // releasing the memory from the heap
    delete pi;
    delete pi1;
    pi = nullptr; // we can set the pointer to nullptr after the memory is released.
    pi1 = nullptr;
}

class Simple {
public:
    Simple() { std::cout << "Object of class simple being constructed\n"; };

    ~Simple() { std::cout << "Object of class simple being destructed\n"; };

    void go() { std::cout << "Object of class simple going ...\n"; };
};

void test_arrays() {
    // test bascic-type arrays
    int myIntArray[]{1, 2, 3, 4, 5};

    // basic-type array on the heap
    int *otherIntArray{new(std::nothrow) int[5]};
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

    Simple *oArray{new Simple[3]};
    delete[] oArray;
    oArray = nullptr;
}

void test_unique_pointer() {
    // unique_pointer uses value initialization. Basic types are initialized to zero and objects are default-constructed.
    // C++ 20 has make_new_for_overwrite() that does not have value initialization.
    auto mySmartPointer{std::make_unique<Simple>()};
    mySmartPointer->go();

    // Calling the pointer by its constructor
    std::unique_ptr<Simple> mySmarterPointer{new Simple{}};

    mySmartPointer.reset();             // just resets the pointer
    mySmartPointer.reset(new Simple{}); // free the old one and assigns to a new one

    Simple *normalPointer{mySmarterPointer.release()}; // gets the ownership from smart pointer to the new pointer
    delete normalPointer;
    normalPointer = nullptr;

    // unique_pointer cannot be copied but can be moved!
    // we shall check this out again later.
}

class Foo {
public:
    Foo(int in) : data_{in} {};
    int data_;
};

void test_shared_pointer() {
    // Simple use of shared pointer
    std::shared_ptr<Simple> mySharedPointer{std::make_shared<Simple>()};

    // using auto to make a shared pointer
    auto myOtherSharedPointer{std::make_shared<Simple>()};

    // to not use value initialization, this can be used (C++ 20)
    // auto myPointer {make_shared_for_overwrite<Simple>()};

    // shared pointer also supports .get and .reset methods like unique pointer

    // uses reference counting to know when to free the resource that is points to

    // creating another pointer from an existing one
    auto smartPointer1{std::make_shared<Simple>()};
    auto smartPointer2{smartPointer1};

    // custom deleters shall be checked later on

    // a technic called "aliasing" with shared pointers
    // it is used to point to members of the class while maintaining a pointer to the calss obj
    auto foo{std::make_shared<Foo>(42)};
    auto aliasing{std::shared_ptr<int>{foo, &foo->data_}};
}

void useWeakPointer(std::weak_ptr<Simple> &in) {
    auto resource{in.lock()}; // returns a shared pointer to the resource!
    if (resource) {
        std::cout << "Resource allocated and being used!\n";
    } else {
        std::cout << "Resource Not allocated!\n";
    }
}

void test_weak_pointer() {
    auto p1{std::make_shared<Simple>()};
    std::weak_ptr<Simple> p2{p1};

    useWeakPointer(p2);
    p1.reset();
    useWeakPointer(p2);
}

void test_memory_management() {
    // test_basic();
    // test_arrays();
    // test_unique_pointer();
    // test_shared_pointer();
    test_weak_pointer();
}