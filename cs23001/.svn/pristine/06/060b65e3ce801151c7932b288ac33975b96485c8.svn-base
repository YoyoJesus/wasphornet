// bigint Test Program
//
// Tests:  int constructor, uses ==
// 
// NEED TO IMPLEMENT
//
#include <iostream> 
#include <cassert>
#include "bigint.hpp"


//===========================================================================
int main () {
    {

        // VERY INCOMPLETE set of tests.


        //------------------------------------------------------
        // Setup fixture
        bigint left(0);
        bigint right(0);
        bigint result;

        // Test 
        result = left + right;

        // Verify
        assert(left   == 0);
        assert(right  == 0);
        assert(result == 0);
    }

    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(0);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 0);
      assert(result == 1);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(1);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 1);
      assert(result == 2);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(0);
      bigint right(8);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 0);
      assert(right  == 8);
      assert(result == 8);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(99);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 99);
      assert(result == 100);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(10);
      bigint right(990);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 10);
      assert(right  == 990);
      assert(result == 1000);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(100);
      bigint right(1000);
      bigint result;

      //Test
      result = left + right;

      // Verify
      assert(left   == 100);
      assert(right  == 1000);
      assert(result == 1100);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(10000);
      bigint right(1);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 10000);
      assert(right  == 1);
      assert(result == 10001);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(10000);
      bigint right(100);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left == 10000);
      assert(right == 100);
      assert(result == 10100);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(0);
      bigint right(9999);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 0);
      assert(right  == 9999);
      assert(result == 9999);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(99999);
      bigint right(10000);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 99999);
      assert(right  == 10000);
      assert(result == 109999);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(5);
      bigint right(100);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 5);
      assert(right  == 100);
      assert(result == 105);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(999);
      bigint right(100000);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 999);
      assert(right  == 100000);
      assert(result == 100999);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left("99");
      bigint right("1245629017832");
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == "99");
      assert(right  == "1245629017832");
      assert(result == "1245629017931");
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(0);
      bigint right("124529017832");
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left == 0);
      assert(right == "124529017832");
      assert(result == "124529017832");
    }

    std::cout << "Done with testing addition." << std::endl;
    return 0;
}

