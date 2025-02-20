//  String class test program
//
//  Tests: Char Array Ctor
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str("abcde");

        // VERIFY
        assert(str == "abcde");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        char x[8] = {'a','b','c','d','e','1','2','9'};
        String  str(x);

        // VERIFY
        assert(str == String(x));
    }

    {
    
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        char x[3];
        String  str(x);

        // VERIFY
        assert(str == String(x));
    }

    std::cout << "Done testing Char Array Ctor" << std::endl;
}