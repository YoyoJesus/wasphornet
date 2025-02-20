// bigint Test Program
//
// Tests:  times_10, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main () {
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(3);

        // Test 
        bi = bi.timesDigit(4);
        std::cout <<"DIGIT MULTIPLY RESULT: " << bi << std::endl;
        // Verify
        assert(bi == 12);
    }

     {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(12);

        // Test 
        bi = bi.timesDigit(3);
        std::cout << "DIGIT MULTIPLY RESULT: " << bi << std::endl;

        // Verify
        assert(bi == 36);
    
    }

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(1246);

        // Test 
        bi = bi.timesDigit(7);
        std::cout <<"DIGIT MULTIPLY RESULT: " << bi << std::endl;

        // Verify
        assert(bi == 8722);
    
    }
    
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(99234);

        // Test 
        bi = bi.timesDigit(9);
        std::cout << "DIGIT MULTIPLY RESULT: " << bi << std::endl;

        // Verify
        assert(bi == 893106);
    
    }

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("126983233223");

        // Test 
        bi = bi.timesDigit(6);
        std::cout <<"DIGIT MULTIPLY RESULT: " << bi << std::endl;

        // Verify
        assert(bi == "761899399338");
    
    }

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("99992929492949249");

        // Test 
        bi = bi.timesDigit(0);
        std::cout <<"DIGIT MULTIPLY RESULT: " << bi << std::endl;

        // Verify
        assert(bi == 0);
    }

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("999999999");

        // Test 
        bi = bi.timesDigit(1);
        std::cout <<"DIGIT MULTIPLY RESULT: " << bi << std::endl;

        // Verify
        assert(bi == "999999999");
    }

    std::cout << "Done testing bigint * digit" << std::endl;
    return 0;
}
