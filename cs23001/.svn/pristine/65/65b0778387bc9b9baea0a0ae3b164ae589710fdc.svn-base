//  String class test program
//
//  Tests: NotEqual
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        String one = 'a';
        String two = 'b';
        
        bool result = one != two;
        std::cout << "NotEqual Result: " << result << std::endl;
        
        assert(result == true);
    }


    {
        String one = "abcd";
        String two = "bcde";
        
        bool result = two != one;
        std::cout << "NotEqual Result: " << result << std::endl;
        
        assert(result == true);
    }

    {
        String one;
        String two = 'b';
        
        bool result = one != two;
        std::cout << "LessThan Result: " << result << std::endl;
        
        assert(result == true);
    }

    {
        String one;
        String two = "bcdasdwrwasws";
        
        bool result = one != two;
        std::cout << "LessThan Result: " << result << std::endl;
        
        assert(result == true);
    }
    
    std::cout << "Done Testing Not Equal" << std::endl;
}