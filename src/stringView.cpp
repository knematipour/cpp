#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>

void test_string_literals()
{
    char *ptr{"hello"};            // causes compiler warning
    ptr[1] = 'o';                  // creates undefined behavior, compiler warning about converting string constant to char*
    std::cout << ptr << std::endl; // causes "segmentation fault"
}

void test_raw_string_literals()
{
    const char *str1{R"(Hello "World!"!)"};
    std::cout << str1 << "\n";

    const char *str2{R"(
        Line1 is here!
        Line2 is here!
    )"};
    std::cout << str2 << "\n";
}

void test_std_string()
{
    std::string a{"123"};
    std::string b{"345"};
    std::string c{"123"};

    if (a == b)
    {
        std::cout << "will never print this!\n";
    }
    else
    {
        std::cout << "will always print this!\n";
    }

    if (!a.compare(c))
    {
        std::cout << "this will be printed!\n";
    }
    std::cout << a + b << "\n";

    // CTAD with std::string
    std::vector names{"Kaveh", "Seda", "Jack"};

    long double pi{3.14159265358979323846264338L};
    std::string piStr{std::to_string(pi)};
    std::cout << piStr << "\n";

    std::string si{"100"};
    int i{std::stoi(si)};
    std::cout << "si: " << si << "\n";
}

void test_strtok()
{
    char input[100] = "A bird came down the walk";
    char *token = std::strtok(input, " "); // return pointer to first character that is not in delim (second parameter)
    while (token != NULL)
    {
        std::cout << std::quoted(token) << '\n';
        token = std::strtok(NULL, " "); // second call with NULL means use the same input as before.
    }
}

void test_c_str()
{
    std::string str{"Hi there, this is Kaveh!"};

    // created an array big enough to store the new array
    char *strArray = new char[str.length() + 1];
    std::strcpy(strArray, str.c_str()); // copying the c_str to the new array

    char *p = std::strtok(strArray, " ");
    while (p != NULL)
    {
        std::cout << p << "\n";
        p = std::strtok(NULL, " ");
    }
    delete[] strArray;
}

void test_string_utilities()
{
    std::string str{"Kaveh is here!"};

    if (str.find("a") != std::string::npos)
    {
        std::cout << "Found!\n";
    }
    std::string sub{str.substr(1)};
    std::cout << sub << "\n";

    sub.replace(0, 2, "Ka");
    std::cout << sub << "\n";
}

void printString(std::string_view str)
{
    std::cout << str << "\n";
}

void test_string_view()
{
    std::string_view str{"Hello World!"};
    printString(str);
}

void string_view_test()
{
    // test_string_literals();
    // test_raw_string_literals();
    test_std_string();
    // test_strtok();
    // test_c_str();
    test_string_utilities();
    test_string_view();
}