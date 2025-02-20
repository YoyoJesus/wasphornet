//  String class test program
//
//  Tests: Substr
//

#include "string.hpp"
#include <cassert>

int main() {
    {
        String str("abcdefgh");
        String result1;
        String result2;
        String result3;
        
        result1 = str.substr(0, 0);
        result2 = str.substr(0, 4);
        result3 = str.substr(0, 7);
        
        assert(result1 == "a"); // Expect "a"
        assert(result2 == "abcde"); // Expect "abcd"
        assert(result3 == "abcdefgh"); // Expect "abcdefg"
    }

    {
        String str("Hello World!");
        String result1 = str.substr(0, 4);
        String result2 = str.substr(6, 10);
        String result3 = str.substr(0, 0);

        assert(result1 == "Hello"); // Expect "Hello"
        assert(result2 == "World"); // Expect "World"
        assert(result3 == "H");     // Expect "H"
    }

    std::cout << "All substr tests passed." << std::endl;
    return 0;
}