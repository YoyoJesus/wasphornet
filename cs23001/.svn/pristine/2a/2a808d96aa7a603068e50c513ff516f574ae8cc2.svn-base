#include "string.hpp"
#include <cassert>
#include <iostream>

int main() {
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String strOne("abcde");
        String strTwo("12345");

        // TEST
        String result = strOne + strTwo;
        std::cout << "Concat Result: " << result << std::endl;

        // VERIFY
        assert(strOne == "abcde");
        assert(strTwo == "12345");
        assert(result == "abcde12345");
    }
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String strOne("ab");
        String strTwo("ab");


        // TEST
        String result = strOne + strTwo;
        std::cout << "Concat Result: " << result << std::endl;

        // VERIFY
        assert(strOne == "ab");
        assert(strTwo == "ab");
        assert(result == "abab");
    }
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String strOne("abab");
        String strTwo("");

        // TEST
        String result = strOne + strTwo;
        std::cout << "Concat Result: " << result << std::endl;

        // VERIFY
        assert(strOne == "abab");
        assert(strTwo == "");
        assert(result == "abab");
    }
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String strOne("ab");

        // TEST
        String result = strOne + strOne;
        std::cout << "Concat Result: " << result << std::endl;

        // VERIFY
        assert(strOne == "ab");
        assert(result == "abab");
    }
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String strOne("ab");

        // TEST
        String result = strOne += strOne;
        std::cout << "Concat Result: " << result << std::endl;

        // VERIFY
        assert(result == "abab");
    }
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String strOne("abab");

        // TEST
        String result = strOne += strOne;
        std::cout << "Concat Result: " << result << std::endl;

        // VERIFY
        assert(result == "abababab");
    }

    std::cout << "Done testing Concat." << std::endl;

    return 0;
}