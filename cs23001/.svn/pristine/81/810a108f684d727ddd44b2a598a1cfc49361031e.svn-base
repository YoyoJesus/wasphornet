//  String class test program
//
//  Tests: FindChar
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        String one = "abcde";
        char two = 'd';
        
        int result = one.findch(0, two); 
        std::cout << "FindChar Result: " << result << std::endl;
        
        assert(result == 3);
    
    }

    {
        String one = "abcde";
        char two = 'c';
        
        int result = one.findch(0, two); 
        std::cout << "FindChar Result: " << result << std::endl;
        
        assert(result == 2);
    
    }

    {
        String one = "abcde1234";
        char two = '3';
        
        int result = one.findch(3, two); 
        std::cout << "FindChar Result: " << result << std::endl;
        
        assert(result == 7);
    
    }

    {
        String one = "abcde1234";
        char two = 'z';
        
        int result = one.findch(3, two); 
        std::cout << "FindChar Result: " << result << std::endl;
        
        assert(result == -1);
    
    }

    std::cout << "Done Testing FindChar" << std::endl;
}