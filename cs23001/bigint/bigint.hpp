/**
   * Austin  Sternberg
   * bigint
   * cs23001
   */

//This header contains all of the classes and definitions needs for the bigint.cpp file

#ifndef CS2_BIGINT_HPP_
#define CS2_BIGINT_HPP_

#include <iostream>
#include <fstream>

const int CAPACITY = 500;

class bigint {
public:
    bigint();
    bigint(int);
    bigint(const char[]);

    void debugPrint(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream&, bigint rhs);
    friend std::istream& operator>>(std::istream&, bigint& rhs);

    bool operator== (bigint rhs);
    bigint operator+(bigint rhs) const;
    int operator[]  (int i) const;
    bigint operator*(bigint);

    bigint timesDigit(int) const;
    bigint times10(int) const;

    bigint nfact(int num);
    int trailingZeros() const;

private:
    int barray[CAPACITY];
};

std::ostream& operator<<(std::ostream&, bigint rhs);
std::istream& operator>>(std::istream&, bigint& rhs);

#endif