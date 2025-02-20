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
        bi = bi.times10(0);

        // Verify
        assert(bi == 3);
    }
    
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(7);

        // Test 
        bi = bi.times10(2);

        // Verify
        assert(bi == 700); 
    }

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(400);

        // Test 
        bi = bi.times10(2);
        // Verify
        assert(bi == 40000);
    } 

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("1000000000000");

        // Test 
        bi = bi.times10(2);
        // Verify
        assert(bi == "100000000000000"); 
    } 
  
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("9843642718302843");

        // Test 
        bi = bi.times10(6);
        // Verify
        assert(bi == "9843642718302843000000");
    } 

  
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("9843642718302843");

        // Test 
        bi = bi.times10(0);
        // Verify
        assert(bi == "9843642718302843"); 
    }

    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("9843642718302843");

        // Test 
        bi = bi.times10(10);
        // Verify
        assert(bi == "98436427183028430000000000");
    } 

     {
        //------------------------------------------------------
        // Setup fixture
        bigint bi("2");

        // Test 
        bi = bi.times10(100);
        // Verify
        assert(bi == "20000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
     }
    std::cout << "Done testing times_10" << std::endl;
    return 0;
}

