//File:        string.hpp
//       
//Version:     1.1
//Date:        Spring 2024
//Author:      Dr. J. Maletic
//
//Description: Interface definition of String class for Project 2, milestone 1.
//
// To use the supplied test oracles you will need to use this interface and namings.
// You must also have all of these methods and functions defined for your string class.
//
// You will either have use this interface or call your methods through this interface.
//
// You need to implement all of the methods and funcitons declared here.
//

#ifndef CS23001_STRING_INTERFACE_HPP
#define CS23001_STRING_INTERFACE_HPP

#include <iostream>

const int STRING_SIZE = 256;                      //The size of the String.

// CLASS INV:   str[length()] == 0 &&
//              0 <= length() <= capacity() &&
//              capacity() == STRING_SIZE - 1
class String {
public:
            String        ();                          //Empty string           DONE
            String        (char);                      //Stirng('x')            DONE
            String        (const char[]);              //String("abcd")         DONE

    int     capacity      ()                    const; //Max chars that can be stored  DONE
    int     length        ()                    const; //Number of char in string      DONE
    char&   operator[]    (int);                       //Accessor/Modifier             DONE
    char    operator[]    (int)                 const; //Accessor                      DONE

    String& operator+=    (const String&);             //Concatenation          DONE
    bool    operator==    (const String&)       const;                       // DONE
    bool    operator<     (const String&)       const;                       // DONE
    String  substr        (int, int)            const; //Sub from staring to ending positions        DONE
    int     findch        (int,  char)          const; //Location of charater starting at a position DONE
    int     findstr       (int,  const String&) const; //Location of string starting at a position   DONE

    friend  std::istream& operator>>(std::istream&, String&);       // DONE
    friend  std::ostream& operator<<(std::ostream&, const String&); // DONE

private:
    char str[STRING_SIZE];
};

String  operator+       (String,        const String&); //DONE
bool    operator==      (const char[],  const String&); //DONE
bool    operator==      (char,          const String&); //DONE
bool    operator<       (const char[],  const String&); //DONE
bool    operator<       (char,          const String&); //DONE
bool    operator<=      (const String&, const String&); //DONE
bool    operator!=      (const String&, const String&); //DONE
bool    operator>=      (const String&, const String&); //DONE
bool    operator>       (const String&, const String&); //DONE

#endif
