//  String class test program
//
//  Tests: Subscript
//

#include "string.hpp"
#include <cassert>

//===========================================================================
int main () {
    {
        //------------------------------------------------------
        // SETUP FIXTURE


        char X[5] = {'h','e','l','l','o'};
        
        String  str(X);

        // TEST
        char result = str[0];
        std::cout << "Subscript Result: " << result << std::endl;
        // VERIFY
        assert(str    == String(X));
        assert(result == 'h');
    }


    {
        //------------------------------------------------------
        // SETUP FIXTURE


        char X[5] = {'h','e','l','l','o'};
        
        String  str(X);

        // TEST
        char result = str[4];
        std::cout << "Subscript Result: " << result << std::endl;
        // VERIFY
        //assert(str    == "hello");
        assert(result == 'o');
    }


    {
        //------------------------------------------------------
        // SETUP FIXTURE
        
        String  str("he1lo");

        // TEST
        char result = str[2];
        std::cout << "Subscript Result: " << result << std::endl;
        // VERIFY
        assert(str    == "he1lo");
        assert(result == '1');
    }


    {
        //------------------------------------------------------
        // SETUP FIXTURE
        
        String  str("hello");

        // TEST
        char result = str[1];
        std::cout << "Subscript Result: " << result << std::endl;
        // VERIFY
        assert(str == "hello");
        assert(result != 'h');
    }
    
    std::cout << "Done testing Subscript." << std::endl;
}