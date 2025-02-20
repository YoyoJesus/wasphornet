//  String class test program
//
//  Tests: Default Ctor
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
     {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str;

        // VERIFY
        assert(str == '\0');
    }
    
    std::cout << "Done testing Default Ctor." << std::endl;
}