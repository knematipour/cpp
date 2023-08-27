#include <iostream>
#include <limits>

void test_data_types()
{
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

enum class PieceTypes : unsigned long
{
    King = 1,
    Queen,
    Rook,
    Pawn
};

void test_enum_class()
{
    PieceTypes piece{PieceTypes::King};

    using enum PieceTypes;
    // PieceTypes p {King};
    PieceTypes p{King};
}

void crash_course()
{
    test_data_types();
}