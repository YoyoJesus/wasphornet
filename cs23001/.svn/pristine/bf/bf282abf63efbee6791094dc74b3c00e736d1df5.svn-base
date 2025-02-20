//  String class test program
//
//  Tests: Copy CTOR
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        String one = "abcde";
        String two(one);
        
        assert(one == two);
    
    }
    {
        String one = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        String two(one);
        
        assert(one == two);
    
    }
    {
        String one = "asdfghjklpoiuytrewqzxcvbnmasdfghjklpoiuytrewq";
        String two(one);
        
        assert(one == two);
    
    }

    std::cout << "Done Testing Copy Ctor" << std::endl;
}