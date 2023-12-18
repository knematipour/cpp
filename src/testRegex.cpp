#include "testRegex.h"
#include <iostream>
#include <regex>

// Regex helps with the following:
// 1) Validation: check if the input string is well formatted
// 2) Decision: check what kind of input the string represents
// 3) Parsing: Extracting information from an input string
// 4) Transformation: Search substring and replace them with new ones
// 5) Iteration: Search all occurrences of a substring
// 6) Tokenization: Split string into substring based on a delimiter

// Terminology:
// Pattern: The actual regular expression is a Pattern represented by a string
// Match: Determines if there is a match between regex and the string
// Search: Determines if there is a substring with the pattern
// Replace: substitution pattern

// Anchors: ^ and $ usually match the beginning and the of a string example: ^test$ matches only a substring of test
// wildcard: . represents any one character example: a.c matches abc
// alternation: | represent one of the chars example a|b means either a or b
// Grouping: ()
// Repetition: * + ?

void testRegex() {
    std::cout << "Testing Regex functionality" << std::endl;

    std::string s1{"1ll2"};
    std::regex reg1{"ll"};
    std::smatch m1;

    if (std::regex_match(s1, m1, reg1)) {
        std::cout << "Pattern Matched!" << std::endl;
        
    }else {
        std::cout << "NO MATCH!" << std::endl;
        
    }

}