/**
   * Austin  Sternberg
   * object_construction.cpp
   * cs23001
   */

//This file contains the definitions for the class 'object'

#include "object_construction.hpp"

Object::Object() {
    std::cout << "Defualt Constructor being called" << std::endl;
}

Object::~Object() {
    std::cout << "Destructor being called" << std::endl;
}

Object::Object(const Object& rhs) {
    std::cout << "Copy Constructor being called" << std::endl;
}

Object Object::operator=(const Object& rhs) {
    Object temp;
    std::cout << "Overload Assignment being called" << std::endl;
    return temp;
}