// 
// Kent State University
// CS 23001 - J. Maletic
//
// Part of lab 6 on dynamic memory
//
// Memory allocation and array bounds checking
//
// C/C++ does not check array bounds, so accessing an element of an
//    array outside of its defined size results in Undefined Behavior
//
// TO COMPILE: clang++ -Wall array_bounds_check.cpp -o bounds_check
// TO RUN: ./bounds_check
//           Then enter a postivie interger value at the prompt
//
// Instructions:
//   Read the code.  Then run the program multiple times.  Examing the output.
//   If on wasp/hornet use values of 10, 16, 32, 33, 40
//   If on a Mac use values of 10 16, 17, 20
//
//   What is wrong with this code?
//      This code doesn't do array bounds checking, so it is very possible to overload str1 and initialize some of the parts of str2.
//   Why is no error raised?
//      No error is raised because the compiler doesn't really care about the bounds of either string, and instead just moves forward with the code it is given. It does not check the array bounds.
//   How many bytes are between the start of str1 and str2?
//      There are 5 bytes between the start of str1 and the start of str2, as str1 is allocated at 5 bytes, then str2 starts right behind it.
//   How could you test for this logical error?
//      Testing this logical error is as simple as trying to assign a number greater than five to str1.
//   How could you prevent this type of error?
//      I would simply add an if statement that checks the value given by the user and cuts the size down if the number is greater than 5. I have added it bellow:
//   Include the delete[] at then end and recompile, what changes?


#include <iostream>


int main () {
    char *str1 = new char[5];     //Allocate two arrays on the heap
    char *str2 = new char[20];
    int n=0;

    std::cout  << "str1->char[5]" << std::endl;
    std::cout  << "str2->char[20]" << std::endl;
    std::cout  << "Enter positive integer value: ";  // n > 0
    std::cin >> n;

    if (n > 5) { //fixed code to insure no issues
        std::cout << "Given TO LARGE, reducing to capacity (5)" << std::endl;
        n = 5;
    }

    std::cout  << "Write to array str1:" << std::endl;
    for (int i = 0; i < n; ++i) {   //Write to str1[0...n-1]
        str1[i] = 'X';
        std::cout << "str1[" << i << "] = 'X'" << std::endl;
    }

    std::cout  << "Contents of array str1:" << std::endl;
    for (int i = 0; i < n; ++i) {   //Print str1[0...n-1]
        std::cout << "str1[" << i << "] == " << "|" <<  str1[i] << "|" << std::endl;
    }

    std::cout  << "Contents of array str2:" << std::endl;
    for (int i = 0; i < 20; ++i) {    //Print str2[0...19]
        std::cout << "str2[" << i << "] == " << "|" <<  str2[i] << "|" << std::endl;
    }

    delete[] str1;
    delete[] str2;

    return 0;
}

