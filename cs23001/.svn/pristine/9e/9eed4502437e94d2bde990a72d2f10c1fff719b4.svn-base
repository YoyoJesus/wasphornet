//  Stack class test program
//
//  Tests: dtor
//

#include "stack.hpp"
#include <cassert>
#include <iostream>

//===========================================================================
int main ()
{
    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<int>  x;
        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<int>  x;
        x.push(1);
        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<char>  x;
        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<char>  x;
        x.push('c');
        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }


    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<String>  x;
        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<String>  x;
        x.push("23");
        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<int> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(i);
            assert(x.top() == i);
        }

        x.~stack();
        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<char> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(char(i));
            assert(x.top() == char(i));
        }

        x.~stack();
        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<String> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(i * i);
            assert(x.top() == (i * i));
        }
        
        x.~stack();
        // VERIFY
        assert(x.empty() == true);
    }

     {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<int> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(i);
            assert(x.top() == i);
        }

        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<char> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(char(i));
            assert(x.top() == char(i));
        }

        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<String> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(i * i);
            assert(x.top() == (i * i));
        }

        x.~stack();

        // VERIFY
        assert(x.empty() == true);
    }
    
    std::cout << "Done testing dtor." << std::endl;
    return 0;
}