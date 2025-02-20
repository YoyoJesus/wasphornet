//  String class test program
//
//  Tests: Swap
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("a");
        String strTwo("b");
        // TEST
        str.swap(strTwo);

        // VERIFY
        assert(str == "b");
        assert(strTwo == "a");
    }
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("aaaaaaaaaaaaaa");
        String strTwo("bbbbbbbbbbbbbbb");
        // TEST
        str.swap(strTwo);

        // VERIFY
        assert(str == "bbbbbbbbbbbbbbb");
        assert(strTwo == "aaaaaaaaaaaaaa");
    }

    std::cout << "Done testing Swap." << std::endl;
}