/**
   * Austin  Sternberg
   * object_construction.hpp
   * cs23001
   */

//This file contains the class information for the object 'object'

#ifndef OBJECT_CONSTRUCTION_HPP_
#define OBJECT_CONSTRUCTION_HPP_

#include <iostream>

class Object {
public:
    Object();
    ~Object();
    Object(const Object&);
    Object operator=(const Object&);
private:
};

#endif