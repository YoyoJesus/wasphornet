/**
   * Austin  Sternberg
   * bigint
   * cs23001
   */

//This file contains more tests for milestone #2 of bigint
#include "bigint.hpp"

int main() {
    //open provided file
    std::ifstream in("data1-1.txt");
    if(!in) { //if file opening failes, alert user and exit program
        std::cerr << "Could not open data1-1.txt" <<std::endl;
        exit(1);
    }

    bigint one;
    bigint two;

    //iterate through the given values in the text file
    while(in >> one && in >> two) {
        //print the initial values of the first two values in the text file
        std::cout << "First Bigint: " << one << std::endl;
        std::cout << "Second Bigint: "  << two << std::endl;

        //add both bigints toghether and print result
        bigint result = one + two;
        std::cout << "Sum of these Bigints: " << result << std::endl;
        std::cout << std::endl;
    }

    in.close();
    return 0;
}