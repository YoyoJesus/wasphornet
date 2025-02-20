//  String class test program
//
//  Tests: Char Ctor
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
     {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str('X');

        // VERIFY
        assert(str == 'X');
    }


    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str('1');

        // VERIFY
        assert(str == '1');
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str(' ');

        // VERIFY
        assert(str == ' ');
    }
    
    std::cout << "Done testing Char Ctor." << std::endl;
}