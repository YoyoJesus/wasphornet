//  Stack class test program
//
//  Tests: assignment operator
//

#include "stack.hpp"
#include <cassert>
#include <iostream>

int main() {
    {
        //------------------------------------------------------
        // TEST: stack<char>

        stack<char> x;
        x.push('c');

        stack<char> x2;
        x2 = x;

        assert(!x.empty());
        assert(!x2.empty());
        assert(x.top() == 'c');
        assert(x2.top() == 'c');
    }

    {
        //------------------------------------------------------
        // TEST: stack<String>

        stack<String> x;
        x.push("23");

        stack<String> x2;
        x2 = x;

        assert(!x.empty());
        assert(!x2.empty());
        assert(x.top() == "23");
        assert(x2.top() == "23");
    }

    {
        //------------------------------------------------------
        // TEST: stack<int>

        stack<int> x;
        x.push(1);

        stack<int> x2;
        x2 = x;

        if (!x.empty())
            x.pop();

        if (!x2.empty())
            x2.pop();

        assert(x.empty());
        assert(x2.empty());
    }

    {
        //------------------------------------------------------
        // TEST: stack<char>

        stack<char> x;
        x.push('c');

        stack<char> x2;
        x2 = x;

        x2.pop();
        x.pop();

        assert(x.empty());
        assert(x2.empty());
    }

    {
        //------------------------------------------------------
        // TEST: stack<String>

        stack<String> x;
        x.push("23");

        stack<String> x2;
        x2 = x;

        x2.pop();
        x.pop();

        assert(x.empty());
        assert(x2.empty());
    }

    {
        //------------------------------------------------------
        // TEST: stack<int>

        stack<int> x;
        for (int i = 0; i <= 1000; ++i){
            x.push(i);
            assert(x.top() == i);
        }

        stack<int> x2;
        x2 = x;

        for (int i = 1000; i >= 0; --i) {
            assert(x.pop() == i);
            assert(x2.pop() == i);
        }

        assert(x.empty());
        assert(x2.empty());
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}