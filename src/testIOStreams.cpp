#include "testIOStreams.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

// the list streams in IOSTREAM:
// cout output console
// cin  input console
// cerr writes to error console (unbuffered)
// clog buffered version of cerr

// general sources are: console, file, strings

std::string readName(std::istream &stream) {
    std::string name;
    while (stream) { // Or: while (!stream.fail()) {
        int next{stream.get()};
        if (!stream || next == std::char_traits<char>::eof())
            break;
        name += static_cast<char>(next);// Append character.
    }
    return name;
}


void testIOStreams() {
    std::cout << "Test IO Streams" << std::endl;

    // basic output stream methods: write and put
    const char *hello{"Hello World!\n"};
    std::cout.write(hello, strlen(hello));
    std::cout.put('a');
    std::cout << "abc";
    std::cout.flush(); // flushes the stream std::endl does the same thing
    // check is the stream is ready
    if (std::cout.good()) {
        std::cout << "Stream is good to go!" << std::endl;

    }

    std::cout << "abc\n";
    std::cout.flush();
    if (std::cout.fail()) {
        std::cerr << "Flushing the buffer failed!\n" << std::endl; // normally not printed!

    }

    // stream manipulators
    // boolalpha, noboolalpha, hex, oct, dec:, setpricision, setw:, setfill: ,quoted, put_money

    // to print out hex values of numbers
    int i{9};
    std::cout << std::uppercase << std::hex << "0x" << std::setfill('0') << std::setw(2) << i << std::endl;

    // input basics
//    std::string str1{};
//    std::cin >> str1;
//    std::cout << "Hello " << str1 << std::endl;

    std::ofstream ofstream{"test.txt", std::ios_base::trunc};
    if (!ofstream.good()){
        std::cerr << "Error opening the file!\n";
        return;
    }

    std::cout << "Writing to file!" << std::endl;
    
    ofstream << "First line of text written to a file!\n";


}