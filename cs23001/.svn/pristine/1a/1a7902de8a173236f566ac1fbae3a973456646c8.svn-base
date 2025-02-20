#include "string.hpp"
#include <cassert>

int main() {
    // Empty String
    {
        String input("");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {""};
        assert(words == oracle);
        std::cout << "Empty String test passed!" << std::endl;
    }

    // Single Character Split
    {
        String input("Hello,World");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"Hello", "World"};
        assert(words == oracle);
        std::cout << "Single Character Split test passed!" << std::endl;
    }

    // Multiple Splits
    {
        String input("apple,banana,orange");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"apple", "banana", "orange"};
        assert(words == oracle);
        std::cout << "Multiple Splits test passed!" << std::endl;
    }

    // No Split Character Found
    {
        String input("abcdefg");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"abcdefg"};
        assert(words == oracle);
        std::cout << "No Split Character Found test passed!" << std::endl;
    }

    // Split at Beginning and End
    {
        String input(",apple,banana,orange,");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"", "apple", "banana", "orange", ""};
        assert(words == oracle);
        std::cout << "Split at Beginning and End test passed!" << std::endl;
    }

    // Split Character at End
    {
        String input("apple,banana,orange,");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"apple", "banana", "orange", ""};
        assert(words == oracle);
        std::cout << "Split Character at End test passed!" << std::endl;
    }

    // Split Character at Beginning
    {
        String input(",apple,banana,orange");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"", "apple", "banana", "orange"};
        assert(words == oracle);
        std::cout << "Split Character at Beginning test passed!" << std::endl;
    }

    // Multiple Consecutive Split Characters
    {
        String input("apple,,banana,,orange");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"apple", "", "banana", "", "orange"};
        assert(words == oracle);
        std::cout << "Multiple Consecutive Split Characters test passed!" << std::endl;
    }

    // Split Character as First Character
    {
        String input(",apple,banana");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"", "apple", "banana"};
        assert(words == oracle);
        std::cout << "Split Character as First Character test passed!" << std::endl;
    }

    // Split Character as Last Character
    {
        String input("apple,banana,");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"apple", "banana", ""};
        assert(words == oracle);
        std::cout << "Split Character as Last Character test passed!" << std::endl;
    }

    // Test splitting by comma (,)
    {
        String input("Hello,World,Welcome");
        std::vector<String> words = input.split(',');

        std::vector<String> oracle = {"Hello", "World", "Welcome"};
        assert(words == oracle);
        std::cout << "Split comma test passed!" << std::endl;
    }

    // Test splitting by hyphen (-)
    {
        String input("one-two-three");
        std::vector<String> words = input.split('-');

        std::vector<String> oracle = {"one", "two", "three"};
        assert(words == oracle);
        std::cout << "Split hyphen test passed!" << std::endl;
    }

    // Test splitting by dot (.)
    {
        String input("file1.txt,file2.txt,file3.txt");
        std::vector<String> words = input.split('.');

        std::vector<String> oracle = {"file1", "txt,file2", "txt,file3", "txt"};
        assert(words == oracle);
        std::cout << "Split dot test passed!" << std::endl;
    }

    // Test splitting by space ( )
    {
        String input("This is a test");
        std::vector<String> words = input.split(' ');

        std::vector<String> oracle = {"This", "is", "a", "test"};
        assert(words == oracle);
        std::cout << "Split space test passed!" << std::endl;
    }

    std::cout << "All split tests passed!" << std::endl;

    return 0;
}