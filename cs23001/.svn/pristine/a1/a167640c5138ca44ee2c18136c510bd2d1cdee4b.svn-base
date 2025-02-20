#include <iostream>
#include "string.hpp"

int main (){

	{
		//string variables
		String str1('a');
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(str1 < str2);
	}
	{
		//string variables
		String str1('b');
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(!(str1 < str2));
	}
	{
		//string variables
		String str1('c');
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(!(str1 < str2));
	}
	{
		//string variables
		String str1("cat");
		String str2("bats");

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(!(str1 < str2));
	}
	{
		//string variables
		String str1("banana");
		String str2("bats");

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(str1 < str2);
	}
	{
		//string variables
		String str1('b');
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(str1 <= str2);
	}
	{
		//string variables
		String str1('q');
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(!(str1 <= str2));
	}
	{
		//string variables
		String str1("banana");
		String str2("banana");

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(str1 <= str2);
	}
	{
		//string variables
		String str1("aaaaaaa");
		String str2('a');

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(!(str1 <= str2));
	}
	{
		//string variables
		String str1;
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(str1 <= str2);
	}
	{
		//string variables
		String str1;
		String str2('b');

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(str1 < str2);
	}
	{
		//string variables
		String str1('a');
		String str2;

		//testing
		std::cout << "Testing " << str1 << " < " << str2 << std::endl;

		//check
		assert(!(str1 < str2));
	}
	{
		//string variables
		String str1('a');
		String str2;

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(!(str1 <= str2));
	}
	{
		//string variables
		String str1('a');
		String str2;

		//testing
		std::cout << "Testing " << str1 << " <= " << str2 << std::endl;

		//check
		assert(!(str1 <= str2));
	}
	{
		//string variables
		String str1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		String str2("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

		//check
		assert((str1 <= str2));
	}
	{
		//string variables
		String str1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		String str2;

		//check
		assert(!(str1 <= str2));
	}

std::cout << "DONE TESTING LESS THAN" << std::endl;

return 0;
}
