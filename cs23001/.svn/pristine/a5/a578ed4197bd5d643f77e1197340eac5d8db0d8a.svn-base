//  String class test program
//
//  Tests: FindString
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        String one = "helloworld";
        String two = "world";
        
        int result = one.findstr(0, two); 
        std::cout << "FindString Result: " << result << std::endl;
        
        assert(result == 5);
    
    }

 
    {
        String one = "helloworld";
        String two = "hello";
        
        int result = one.findstr(0, two); 
        std::cout << "FindString Result: " << result << std::endl;
        
        assert(result == 0);
    
    }  


    {
        String one = "helloworld";
        String two = "rld";
        
        int result = one.findstr(3, two); 
        std::cout << "FindString Result: " << result << std::endl;
        
        assert(result == 4);
    
    }

    {
        String one = "helloworld";
        String two = "zero";
        
        int result = one.findstr(3, two); 
        std::cout << "FindString Result: " << result << std::endl;
        
        assert(result == -1);
    
    }

    std::cout << "Done Testing FindString" << std::endl;

}